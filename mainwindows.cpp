#include "mainwindows.h"
#include "ui_mainwindows.h"
#include "accountdialog.h"
#include <QMessageBox>
#include <QStatusBar>
#include <QDateTime>
#include <QFileDialog>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentAccount(nullptr)
    , dbManager(new DatabaseManager(this))
    , isDarkMode(false)
{
    ui->setupUi(this);

    if (!dbManager->openDatabase()) {
        QMessageBox::critical(this, "Erreur critique", "Impossible d'ouvrir la base de données.\nL'application va se fermer.");
        QApplication::quit();
        return;
    }

    dbManager->loadAccounts(accountsList);

    if (accountsList.isEmpty()) {
        dbManager->initializeDefaultData();
        dbManager->loadAccounts(accountsList);
    }

    dbManager->loadTransactions(transactionHistory);

    statusBar()->showMessage("Base de données chargée. " + QString::number(accountsList.size()) + " compte(s) trouvé(s).");

    connect(ui->createButton, &QPushButton::clicked, this, &MainWindow::onCreateAccount);
    connect(ui->depositButton, &QPushButton::clicked, this, &MainWindow::onDeposit);
    connect(ui->withdrawButton, &QPushButton::clicked, this, &MainWindow::onWithdraw);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearchAccount);
    connect(ui->clearSearchButton, &QPushButton::clicked, this, &MainWindow::onClearSearch);
    connect(ui->displayButton, &QPushButton::clicked, this, &MainWindow::onDisplayDetails);
    connect(ui->checkBalanceButton, &QPushButton::clicked, this, &MainWindow::onCheckBalance);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::onReset);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::onExit);
    connect(ui->interestButton, &QPushButton::clicked, this, &MainWindow::onCalculateInterest);
    connect(ui->darkModeButton, &QPushButton::clicked, this, &MainWindow::onToggleDarkMode);
    connect(ui->exportButton, &QPushButton::clicked, this, &MainWindow::onExportCSV);
    connect(ui->importButton, &QPushButton::clicked, this, &MainWindow::onImportCSV);
    connect(ui->currencyComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onCurrencyChanged);
    connect(ui->amountLineEdit, &QLineEdit::returnPressed, this, &MainWindow::onDeposit);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dbManager;
}

// --- PARTIE 3.1 & 5 : CRÉATION DE COMPTE ---
void MainWindow::onCreateAccount()
{
    statusBar()->showMessage("Ouverture du formulaire de création...");
    AccountDialog dialog(this, isDarkMode);

    if (dialog.exec() == QDialog::Accepted) {
        BankAccount newAccount = dialog.getCreatedAccount();

        for (const BankAccount &acc : accountsList) {
            if (acc.getAccountNumber() == newAccount.getAccountNumber()) {
                QMessageBox msgBox(this);
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.setWindowTitle("Erreur");
                msgBox.setText("Un compte avec ce numéro existe déjà dans le système !");
                styleMessageBox(&msgBox);
                msgBox.exec();
                statusBar()->showMessage("Échec : Numéro de compte déjà utilisé.");
                return;
            }
        }

        if (!dbManager->insertAccount(newAccount)) {
            QMessageBox msgBox(this);
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setWindowTitle("Base de données");
            msgBox.setText("Erreur lors de l'enregistrement du compte dans la base de données !");
            styleMessageBox(&msgBox);
            msgBox.exec();
            statusBar()->showMessage("Échec : erreur base de données.");
            return;
        }

        dbManager->addTransaction(newAccount.getAccountNumber(), "Compte créé");

        accountsList.append(newAccount);
        currentAccount = &accountsList.last();

        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Succès");
        msgBox.setText("Le compte de " + newAccount.getDepositorName() + " a été créé avec succès !");
        styleMessageBox(&msgBox);
        msgBox.exec();
        statusBar()->showMessage("Nouveau compte enregistré avec succès.");

        onDisplayDetails();
    } else {
        statusBar()->showMessage("Création de compte annulée.");
    }
}

// --- PARTIE 3.2 & 5 : RECHERCHE DE COMPTE ---
void MainWindow::onSearchAccount()
{
    QString searchText = ui->searchLineEdit->text().trimmed();

    if (searchText.isEmpty()) {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Saisie incomplète");
        msgBox.setText("Veuillez entrer un numéro de compte à rechercher.");
        styleMessageBox(&msgBox);
        msgBox.exec();
        return;
    }

    bool ok;
    int searchNum = searchText.toInt(&ok);
    if (!ok || searchNum <= 0) {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Format invalide");
        msgBox.setText("Le numéro de compte doit être un nombre entier positif !");
        styleMessageBox(&msgBox);
        msgBox.exec();
        return;
    }

    QString selectedType = ui->searchTypeComboBox->currentText();
    QString inputPin = ui->pinLineEdit->text().trimmed();

    currentAccount = nullptr;
    for (int i = 0; i < accountsList.size(); ++i) {
        if (accountsList[i].getAccountNumber() == searchNum) {
            if (selectedType == "Tous" || accountsList[i].getAccountType() == selectedType) {
                if (!verifyAccountPin(searchNum, inputPin)) {
                    QMessageBox msgBox(this);
                    msgBox.setIcon(QMessageBox::Critical);
                    msgBox.setWindowTitle("Accès refusé");
                    msgBox.setText("PIN incorrect pour ce compte !");
                    styleMessageBox(&msgBox);
                    msgBox.exec();
                    statusBar()->showMessage("Échec : PIN incorrect.");
                    return;
                }
                currentAccount = &accountsList[i];
            }
            break;
        }
    }

    if (currentAccount != nullptr) {
        ui->detailDisplay->setText(currentAccount->getAccountDetails());
        statusBar()->showMessage("Compte actif : " + currentAccount->getDepositorName());
        ui->pinLineEdit->clear();
    } else {
        ui->detailDisplay->clear();
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Introuvable");
        msgBox.setText("Aucun compte trouvé avec le numéro " + searchText + (selectedType != "Tous" ? " et le type " + selectedType : "") + ".");
        styleMessageBox(&msgBox);
        msgBox.exec();
        statusBar()->showMessage("Recherche échouée : compte inexistant.");
    }
}

bool MainWindow::verifyAccountPin(int accountNumber, const QString &inputPin)
{
    for (const BankAccount &acc : accountsList) {
        if (acc.getAccountNumber() == accountNumber) {
            return acc.verifyPin(inputPin);
        }
    }
    return false;
}

// --- PARTIE 3.2b : EFFACER LA RECHERCHE ---
void MainWindow::onClearSearch()
{
    ui->searchLineEdit->clear();
    ui->searchTypeComboBox->setCurrentIndex(0);
    ui->pinLineEdit->clear();
    ui->detailDisplay->clear();
    ui->transactionListWidget->clear();
    currentAccount = nullptr;
    statusBar()->showMessage("Recherche effacée.");
}

// --- PARTIE 3.5 : CONSULTER LE SOLDE ---
void MainWindow::onCheckBalance()
{
    if (currentAccount != nullptr) {
        QString currency = ui->currencyComboBox->currentText();
        double balance = currentAccount->getBalance();
        double converted = balance;

        if (currency == "USD") converted = balance * 1.08;
        else if (currency == "GBP") converted = balance * 0.86;

        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Solde");
        msgBox.setText("Compte N° " + QString::number(currentAccount->getAccountNumber()) + "\n" +
                       "Titulaire : " + currentAccount->getDepositorName() + "\n" +
                       "Solde actuel (" + currency + ") : " + QString::number(converted, 'f', 2) + " " + currency);
        styleMessageBox(&msgBox);
        msgBox.exec();
        statusBar()->showMessage("Solde consulté pour " + currentAccount->getDepositorName());
    } else {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Aucun compte");
        msgBox.setText("Veuillez d'abord rechercher ou créer un compte.");
        styleMessageBox(&msgBox);
        msgBox.exec();
    }
}

// --- PARTIE 3.3 & 5 : OPÉRATION DE DÉPÔT ---
void MainWindow::onDeposit()
{
    if (currentAccount == nullptr) {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Erreur");
        msgBox.setText("Veuillez d'abord rechercher ou créer un compte.");
        styleMessageBox(&msgBox);
        msgBox.exec();
        return;
    }

    if (!dbManager->isDatabaseOpen()) {
        QMessageBox::critical(this, "Erreur base de données", "La base de données n'est pas accessible. Opération annulée.");
        return;
    }

    bool ok;
    double amount = ui->amountLineEdit->text().toDouble(&ok);
    if (!ok || amount <= 0) {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Erreur de montant");
        msgBox.setText("Veuillez entrer un montant numérique strictement supérieur à 0.");
        styleMessageBox(&msgBox);
        msgBox.exec();
        return;
    }

    if (currentAccount->deposit(amount)) {
        if (!dbManager->updateAccount(*currentAccount)) {
            QMessageBox::warning(this, "Base de données", "Le dépôt a été effectué en mémoire, mais l'enregistrement en base a échoué.");
        }

        if (!dbManager->addTransaction(currentAccount->getAccountNumber(), "Dépôt de " + QString::number(amount, 'f', 2) + " €")) {
            QMessageBox::warning(this, "Base de données", "Le dépôt a été effectué, mais l'historique n'a pas pu être enregistré.");
        }

        transactionHistory[currentAccount->getAccountNumber()].append("Dépôt de " + QString::number(amount, 'f', 2) + " € | " + QDateTime::currentDateTime().toString(Qt::ISODate));

        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Succès");
        msgBox.setText("Dépôt réussi !\nNouveau solde : " + currentAccount->getBalanceString());
        styleMessageBox(&msgBox);
        msgBox.exec();
        ui->detailDisplay->setText(currentAccount->getAccountDetails());
        statusBar()->showMessage("Dépôt de " + QString::number(amount, 'f', 2) + " € effectué.");
        ui->amountLineEdit->clear();
    }
}

// --- PARTIE 3.4 & 5 : OPÉRATION DE RETRAIT ---
void MainWindow::onWithdraw()
{
    if (currentAccount == nullptr) {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Erreur");
        msgBox.setText("Veuillez d'abord rechercher ou créer un compte.");
        styleMessageBox(&msgBox);
        msgBox.exec();
        return;
    }

    if (!dbManager->isDatabaseOpen()) {
        QMessageBox::critical(this, "Erreur base de données", "La base de données n'est pas accessible. Opération annulée.");
        return;
    }

    bool ok;
    double amount = ui->amountLineEdit->text().toDouble(&ok);
    if (!ok || amount <= 0) {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Erreur de montant");
        msgBox.setText("Veuillez entrer un montant numérique strictement supérieur à 0.");
        styleMessageBox(&msgBox);
        msgBox.exec();
        return;
    }

    if (currentAccount->withdraw(amount)) {
        if (!dbManager->updateAccount(*currentAccount)) {
            QMessageBox::warning(this, "Base de données", "Le retrait a été effectué en mémoire, mais l'enregistrement en base a échoué.");
        }

        if (!dbManager->addTransaction(currentAccount->getAccountNumber(), "Retrait de " + QString::number(amount, 'f', 2) + " €")) {
            QMessageBox::warning(this, "Base de données", "Le retrait a été effectué, mais l'historique n'a pas pu être enregistré.");
        }

        transactionHistory[currentAccount->getAccountNumber()].append("Retrait de " + QString::number(amount, 'f', 2) + " € | " + QDateTime::currentDateTime().toString(Qt::ISODate));

        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Succès");
        msgBox.setText("Retrait réussi !\nNouveau solde : " + currentAccount->getBalanceString());
        styleMessageBox(&msgBox);
        msgBox.exec();
        ui->detailDisplay->setText(currentAccount->getAccountDetails());
        statusBar()->showMessage("Retrait de " + QString::number(amount, 'f', 2) + " € effectué.");
        ui->amountLineEdit->clear();
    } else {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Fonds insuffisants");
        msgBox.setText("Opération refusée : Solde disponible insuffisant !");
        styleMessageBox(&msgBox);
        msgBox.exec();
        statusBar()->showMessage("Échec du retrait : solde insuffisant.");
    }
}

// --- PARTIE 3.6 : AFFICHER LES DÉTAILS ---
void MainWindow::onDisplayDetails()
{
    ui->currencyComboBox->setCurrentIndex(0);
    if (currentAccount != nullptr) {
        ui->detailDisplay->setText(currentAccount->getAccountDetails());
        updateTransactionDisplay();
        statusBar()->showMessage("Détails mis à jour pour " + currentAccount->getDepositorName());
    } else {
        ui->detailDisplay->setText("Aucun compte sélectionné. Veuillez créer un compte ou effectuer une recherche.");
        ui->transactionListWidget->clear();
    }
}

// --- PARTIE 3.7 : RÉINITIALISER L'INTERFACE ---
void MainWindow::onReset()
{
    ui->searchLineEdit->clear();
    ui->searchTypeComboBox->setCurrentIndex(0);
    ui->amountLineEdit->clear();
    ui->currencyComboBox->setCurrentIndex(0);
    ui->pinLineEdit->clear();
    ui->detailDisplay->clear();
    ui->transactionListWidget->clear();
    currentAccount = nullptr;
    statusBar()->showMessage("Champs réinitialisés. Les données de comptes sont conservées en mémoire.");
}

// --- PARTIE 3.8 : QUITTER L'APPLICATION ---
void MainWindow::onExit()
{
    QMessageBox msgBox(this);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle("Quitter");
    msgBox.setText("Êtes-vous sûr de vouloir fermer l'application ?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    styleMessageBox(&msgBox);
    if (msgBox.exec() == QMessageBox::Yes) {
        this->close();
    }
}

// --- BONUS 1 : CALCULATEUR D'INTÉRÊTS ---
void MainWindow::onCalculateInterest()
{
    if (currentAccount == nullptr) {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Aucun compte");
        msgBox.setText("Veuillez d'abord rechercher ou créer un compte.");
        styleMessageBox(&msgBox);
        msgBox.exec();
        return;
    }

    double rate = 0.0;
    if (currentAccount->getAccountType() == "Savings") {
        rate = 0.03;
    } else if (currentAccount->getAccountType() == "Current") {
        rate = 0.005;
    }

    if (rate == 0.0) {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Intérêts");
        msgBox.setText("Ce type de compte ne génère pas d'intérêts.");
        styleMessageBox(&msgBox);
        msgBox.exec();
        return;
    }

    double interest = currentAccount->getBalance() * rate;
    QString message = "Taux d'intérêt annuel : " + QString::number(rate * 100, 'f', 1) + "%\n"
                      "Solde actuel : " + currentAccount->getBalanceString() + "\n"
                      "Intérêts annuels estimés : " + QString::number(interest, 'f', 2) + " €";

    QMessageBox msgBox(this);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("Calculatrice d'intérêts");
    msgBox.setText(message);
    styleMessageBox(&msgBox);
    msgBox.exec();
    statusBar()->showMessage("Intérêts calculés pour " + currentAccount->getDepositorName());
}

// --- BONUS 2 : MODE SOMBRE ---
void MainWindow::onToggleDarkMode()
{
    isDarkMode = !isDarkMode;

    if (isDarkMode) {
        setStyleSheet("QMainWindow { background-color: #1e1e2e; }"
                      "QGroupBox { font: 700 10pt 'Segoe UI'; border: 2px solid #444; border-radius: 8px; margin-top: 12px; padding-top: 12px; background-color: #2d2d44; }"
                      "QGroupBox::title { subcontrol-origin: margin; left: 12px; padding: 0 8px 0 8px; color: #e0e0e0; }"
                      "QPushButton { font: 600 10pt 'Segoe UI'; min-width: 100px; min-height: 36px; padding: 6px 16px; border-radius: 6px; border: none; }"
                      "QPushButton:hover { filter: brightness(1.2); }"
                      "QPushButton:pressed { filter: brightness(0.9); }"
                      "QPushButton:disabled { background-color: #3d3d5c; color: #777; }"
                      "#createButton { background-color: #059669; color: #ffffff; }"
                      "#depositButton { background-color: #2563eb; color: #ffffff; }"
                      "#withdrawButton { background-color: #dc2626; color: #ffffff; }"
                      "#searchButton { background-color: #4b5563; color: #ffffff; min-width: 80px; }"
                      "#clearSearchButton { background-color: #3d3d5c; color: #e0e0e0; border: 2px solid #555; }"
                      "#clearSearchButton:hover { background-color: #4d4d6c; }"
                      "#displayButton { background-color: #0891b2; color: #ffffff; }"
                      "#checkBalanceButton { background-color: #a855f7; color: #ffffff; }"
                      "#resetButton { background-color: #b45309; color: #ffffff; }"
                      "#exitButton { background-color: #6b7280; color: #ffffff; }"
                      "#exitButton:hover { background-color: #4b5563; }"
                      "#interestButton { background-color: #0891b2; color: #ffffff; }"
                      "#darkModeButton { background-color: #7c3aed; color: #ffffff; }"
                      "#exportButton { background-color: #059669; color: #ffffff; }"
                      "#importButton { background-color: #b45309; color: #ffffff; }"
                      "QLineEdit { font: 400 10pt 'Segoe UI'; min-height: 32px; padding: 4px 10px; border: 2px solid #555; border-radius: 6px; background-color: #3d3d5c; color: #ffffff; selection-background-color: #bfdbfe; }"
                      "QLineEdit:focus { border: 2px solid #3b82f6; }"
                      "QTextEdit { font: 400 10pt 'Segoe UI'; border: 2px solid #555; border-radius: 8px; background-color: #2d2d44; color: #ffffff; padding: 12px; }"
                      "QListWidget { font: 400 10pt 'Segoe UI'; border: 2px solid #555; border-radius: 8px; background-color: #2d2d44; color: #ffffff; padding: 8px; }"
                      "QStatusBar { font: 400 9pt 'Segoe UI'; background-color: #0f0f1a; color: #ffffff; padding: 4px 12px; }"
                      "QMenuBar { font: 400 9pt 'Segoe UI'; background-color: #2d2d44; color: #e0e0e0; border-bottom: 1px solid #444; }"
                      "QLabel { font: 400 10pt 'Segoe UI'; color: #e0e0e0; padding: 2px 4px; }"
                      "#currencyLabel { font: 600 10pt 'Segoe UI'; color: #cccccc; padding: 4px 2px; }"
                      "QComboBox { font: 400 10pt 'Segoe UI'; min-height: 32px; padding: 4px 10px; border: 2px solid #555; border-radius: 6px; background-color: #3d3d5c; color: #ffffff; }"
                      "QComboBox:focus { border: 2px solid #3b82f6; }"
                      "QComboBox::drop-down { border: none; width: 28px; }"
                      "QComboBox QAbstractItemView { background-color: #3d3d5c; color: #ffffff; border: 1px solid #555; selection-background-color: #eff6ff; selection-color: #1e40af; }");
        ui->darkModeButton->setText("Mode Clair");
        statusBar()->showMessage("Mode sombre activé.");
    } else {
        setStyleSheet("QMainWindow { background-color: #f5f7fa; }"
                      "QGroupBox { font: 700 10pt 'Segoe UI'; border: 2px solid #d1d5db; border-radius: 8px; margin-top: 12px; padding-top: 12px; background-color: #ffffff; }"
                      "QGroupBox::title { subcontrol-origin: margin; left: 12px; padding: 0 8px 0 8px; color: #1e3a5f; }"
                      "QPushButton { font: 600 10pt 'Segoe UI'; min-width: 100px; min-height: 36px; padding: 6px 16px; border-radius: 6px; border: none; }"
                      "QPushButton:hover { filter: brightness(1.1); }"
                      "QPushButton:pressed { filter: brightness(0.95); }"
                      "QPushButton:disabled { background-color: #e5e7eb; color: #9ca3af; }"
                      "#createButton { background-color: #059669; color: #ffffff; }"
                      "#depositButton { background-color: #2563eb; color: #ffffff; }"
                      "#withdrawButton { background-color: #dc2626; color: #ffffff; }"
                      "#searchButton { background-color: #4b5563; color: #ffffff; min-width: 80px; }"
                      "#clearSearchButton { background-color: #f3f4f6; color: #374151; border: 2px solid #d1d5db; }"
                      "#clearSearchButton:hover { background-color: #e5e7eb; }"
                      "#displayButton { background-color: #0891b2; color: #ffffff; }"
                      "#checkBalanceButton { background-color: #7c3aed; color: #ffffff; }"
                      "#resetButton { background-color: #f59e0b; color: #ffffff; }"
                      "#exitButton { background-color: #374151; color: #ffffff; }"
                      "#interestButton { background-color: #0891b2; color: #ffffff; }"
                      "#darkModeButton { background-color: #7c3aed; color: #ffffff; }"
                      "#exportButton { background-color: #059669; color: #ffffff; }"
                      "#importButton { background-color: #d97706; color: #ffffff; }"
                      "QLineEdit { font: 400 10pt 'Segoe UI'; min-height: 32px; padding: 4px 10px; border: 2px solid #d1d5db; border-radius: 6px; background-color: #ffffff; selection-background-color: #bfdbfe; }"
                      "QLineEdit:focus { border: 2px solid #3b82f6; }"
                      "QTextEdit { font: 400 10pt 'Segoe UI'; border: 2px solid #e5e7eb; border-radius: 8px; background-color: #f9fafb; padding: 12px; }"
                      "QListWidget { font: 400 10pt 'Segoe UI'; border: 2px solid #e5e7eb; border-radius: 8px; background-color: #f9fafb; padding: 8px; }"
                      "QStatusBar { font: 400 9pt 'Segoe UI'; background-color: #1e3a5f; color: #ffffff; padding: 4px 12px; }"
                      "QMenuBar { font: 400 9pt 'Segoe UI'; background-color: #ffffff; color: #111827; border-bottom: 1px solid #e5e7eb; }"
                      "QLabel { font: 400 10pt 'Segoe UI'; color: #4b5563; padding: 2px 4px; }"
                      "#currencyLabel { font: 600 10pt 'Segoe UI'; color: #6b7280; padding: 4px 2px; }"
                      "QComboBox { font: 400 10pt 'Segoe UI'; min-height: 32px; padding: 4px 10px; border: 2px solid #d1d5db; border-radius: 6px; background-color: #ffffff; }"
                      "QComboBox:focus { border: 2px solid #3b82f6; }"
                      "QComboBox::drop-down { border: none; width: 28px; }"
                      "QComboBox QAbstractItemView { background-color: #ffffff; border: 1px solid #e5e7eb; selection-background-color: #eff6ff; selection-color: #1e40af; }");
        ui->darkModeButton->setText("Mode Sombre");
        statusBar()->showMessage("Mode clair activé.");
    }
}

void MainWindow::styleMessageBox(QMessageBox *msgBox) const {
    if (isDarkMode) {
        msgBox->setStyleSheet("QMessageBox { background-color: #2d2d44; color: #e0e0e0; }"
                              "QMessageBox QLabel { color: #e0e0e0; font: 400 10pt 'Segoe UI'; padding: 8px; }"
                              "QMessageBox QPushButton { font: 600 10pt 'Segoe UI'; min-width: 100px; min-height: 36px; padding: 6px 16px; border-radius: 6px; border: none; background-color: #3d3d5c; color: #ffffff; }"
                              "QMessageBox QPushButton:hover { background-color: #4d4d6c; }"
                              "QMessageBox QPushButton:pressed { background-color: #2d2d44; }");
    }
}

// --- BONUS 3 : EXPORT CSV ---
void MainWindow::onExportCSV()
{
    if (accountsList.isEmpty()) {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Export");
        msgBox.setText("Aucun compte à exporter.");
        styleMessageBox(&msgBox);
        msgBox.exec();
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Exporter les comptes", QDir::homePath(), "Fichiers CSV (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Erreur");
        msgBox.setText("Impossible d'ouvrir le fichier en écriture.");
        styleMessageBox(&msgBox);
        msgBox.exec();
        return;
    }

    QTextStream out(&file);
    out << "Nom,Numéro de compte,Type,Solde\n";

    for (const BankAccount &acc : accountsList) {
        out << acc.getDepositorName() << ","
            << acc.getAccountNumber() << ","
            << acc.getAccountType() << ","
            << QString::number(acc.getBalance(), 'f', 2) << "\n";
    }

    file.close();
    QMessageBox msgBox(this);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("Export");
    msgBox.setText("Exportation réussie vers:\n" + fileName);
    styleMessageBox(&msgBox);
    msgBox.exec();
    statusBar()->showMessage("Comptes exportés vers " + fileName);
}

// --- BONUS 4 : IMPORT CSV ---
void MainWindow::onImportCSV()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Importer des comptes", QDir::homePath(), "Fichiers CSV (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Erreur");
        msgBox.setText("Impossible d'ouvrir le fichier en lecture.");
        styleMessageBox(&msgBox);
        msgBox.exec();
        return;
    }

    QTextStream in(&file);
    int importedCount = 0;

    in.readLine();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (fields.size() != 4) continue;

        QString name = fields[0].trimmed();
        int accNum = fields[1].trimmed().toInt();
        QString type = fields[2].trimmed();
        double balance = fields[3].trimmed().toDouble();

        if (name.isEmpty() || accNum <= 0) continue;

        bool exists = false;
        for (const BankAccount &acc : accountsList) {
            if (acc.getAccountNumber() == accNum) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            BankAccount newAccount;
            newAccount.createAccount(name, accNum, type, balance, "0000");
            accountsList.append(newAccount);
            dbManager->insertAccount(newAccount);
            importedCount++;
        }
    }

    file.close();
    QMessageBox msgBox(this);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("Import");
    msgBox.setText(QString("%1 compte(s) importé(s) avec succès.").arg(importedCount));
    styleMessageBox(&msgBox);
    msgBox.exec();
    statusBar()->showMessage(QString("%1 compte(s) importés.").arg(importedCount));
}

// --- BONUS 5 : CONVERTISSEUR DE DEVISES ---
void MainWindow::onCurrencyChanged(int index)
{
    Q_UNUSED(index);

    if (currentAccount == nullptr) {
        ui->detailDisplay->setText("Aucun compte sélectionné. Veuillez créer un compte ou effectuer une recherche.");
        return;
    }

    QString currency = ui->currencyComboBox->currentText();
    double balance = currentAccount->getBalance();
    double converted = balance;

    if (currency == "USD") {
        converted = balance * 1.08;
    } else if (currency == "GBP") {
        converted = balance * 0.86;
    }

    QString details = QString("<b>Account Number:</b> %1<br>"
                             "<b>Account Holder:</b> %2<br>"
                             "<b>Account Type:</b> %3<br>"
                             "<b>Current Balance (%4):</b> %5")
                          .arg(currentAccount->getAccountNumber())
                          .arg(currentAccount->getDepositorName())
                          .arg(currentAccount->getAccountType())
                          .arg(currency)
                          .arg(QString::number(converted, 'f', 2) + " " + currency);

    ui->detailDisplay->setText(details);
}

// --- BONUS 6 : AFFICHER L'HISTORIQUE ---
void MainWindow::updateTransactionDisplay()
{
    ui->transactionListWidget->clear();

    if (currentAccount == nullptr) {
        ui->transactionListWidget->addItem("Aucun compte sélectionné.");
        return;
    }

    int accNum = currentAccount->getAccountNumber();
    if (transactionHistory.contains(accNum)) {
        for (const QString &tx : transactionHistory[accNum]) {
            ui->transactionListWidget->addItem(tx);
        }
    } else {
        ui->transactionListWidget->addItem("Aucune transaction enregistrée pour ce compte.");
    }
}

