#include "mainwindows.h"
#include "ui_mainwindows.h"
#include "accountdialog.h"
#include <QMessageBox>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentAccount(nullptr) // Aucun compte sélectionné au départ
{
    ui->setupUi(this);

    // --- PARTIE 4 : CONNEXIONS DES SIGNAUX & SLOTS ---
    // Connexion des boutons aux slots correspondants
    connect(ui->createButton, &QPushButton::clicked, this, &MainWindow::onCreateAccount);
    connect(ui->depositButton, &QPushButton::clicked, this, &MainWindow::onDeposit);
    connect(ui->withdrawButton, &QPushButton::clicked, this, &MainWindow::onWithdraw);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearchAccount);
    connect(ui->clearSearchButton, &QPushButton::clicked, this, &MainWindow::onClearSearch);
    connect(ui->displayButton, &QPushButton::clicked, this, &MainWindow::onDisplayDetails);
    connect(ui->checkBalanceButton, &QPushButton::clicked, this, &MainWindow::onCheckBalance);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::onReset);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::onExit);

    // Connexion pour la touche Entrée sur le champ de montant
    connect(ui->amountLineEdit, &QLineEdit::returnPressed, this, &MainWindow::onDeposit);

    // Configuration initiale de la barre de statut
    statusBar()->showMessage("Prêt. Créez ou recherchez un compte.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// --- PARTIE 3.1 & 5 : CRÉATION DE COMPTE ---
void MainWindow::onCreateAccount()
{
    statusBar()->showMessage("Ouverture du formulaire de création...");
    AccountDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        // Récupération du compte configuré et validé par le QDialog
        BankAccount newAccount = dialog.getCreatedAccount();

        // Validation Bonus : Éviter les doublons de numéros de compte
        for (const BankAccount &acc : accountsList) {
            if (acc.getAccountNumber() == newAccount.getAccountNumber()) {
                QMessageBox::critical(this, "Erreur", "Un compte avec ce numéro existe déjà dans le système !");
                statusBar()->showMessage("Échec : Numéro de compte déjà utilisé.");
                return;
            }
        }

        // Ajouter le compte à la liste globale
        accountsList.append(newAccount);

        // Mettre à jour le pointeur vers le compte actif (le dernier ajouté)
        currentAccount = &accountsList.last();

        QMessageBox::information(this, "Succès", "Le compte de " + newAccount.getDepositorName() + " a été créé avec succès !");
        statusBar()->showMessage("Nouveau compte enregistré avec succès.");

        // Affichage immédiat des détails
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
        QMessageBox::warning(this, "Saisie incomplète", "Veuillez entrer un numéro de compte à rechercher.");
        return;
    }

    bool ok;
    int searchNum = searchText.toInt(&ok);
    if (!ok || searchNum <= 0) {
        QMessageBox::critical(this, "Format invalide", "Le numéro de compte doit être un nombre entier positif !");
        return;
    }

    QString selectedType = ui->searchTypeComboBox->currentText();

    currentAccount = nullptr;
    for (int i = 0; i < accountsList.size(); ++i) {
        if (accountsList[i].getAccountNumber() == searchNum) {
            if (selectedType == "Tous" || accountsList[i].getAccountType() == selectedType) {
                currentAccount = &accountsList[i];
            }
            break;
        }
    }

    if (currentAccount != nullptr) {
        ui->detailDisplay->setText(currentAccount->getAccountDetails());
        statusBar()->showMessage("Compte actif : " + currentAccount->getDepositorName());
    } else {
        ui->detailDisplay->clear();
        QMessageBox::critical(this, "Introuvable", "Aucun compte trouvé avec le numéro " + searchText + (selectedType != "Tous" ? " et le type " + selectedType : "") + ".");
        statusBar()->showMessage("Recherche échouée : compte inexistant.");
    }
}

// --- PARTIE 3.2b : EFFACER LA RECHERCHE ---
void MainWindow::onClearSearch()
{
    ui->searchLineEdit->clear();
    ui->searchTypeComboBox->setCurrentIndex(0);
    ui->detailDisplay->clear();
    currentAccount = nullptr;
    statusBar()->showMessage("Recherche effacée.");
}

// --- PARTIE 3.5 : CONSULTER LE SOLDE ---
void MainWindow::onCheckBalance()
{
    if (currentAccount != nullptr) {
        QMessageBox::information(this, "Solde",
                                "Compte N° " + QString::number(currentAccount->getAccountNumber()) + "\n" +
                                "Titulaire : " + currentAccount->getDepositorName() + "\n" +
                                "Solde actuel : " + currentAccount->getBalanceString());
        statusBar()->showMessage("Solde consulté pour " + currentAccount->getDepositorName());
    } else {
        QMessageBox::warning(this, "Aucun compte", "Veuillez d'abord rechercher ou créer un compte.");
    }
}

// --- PARTIE 3.3 & 5 : OPÉRATION DE DÉPÔT ---
void MainWindow::onDeposit()
{
    // Validation : Le compte doit exister/être sélectionné
    if (currentAccount == nullptr) {
        QMessageBox::warning(this, "Erreur", "Veuillez d'abord rechercher ou créer un compte.");
        return;
    }

    // Validation : Le montant doit être numérique et positif
    bool ok;
    double amount = ui->amountLineEdit->text().toDouble(&ok);
    if (!ok || amount <= 0) {
        QMessageBox::critical(this, "Erreur de montant", "Veuillez entrer un montant numérique strictement supérieur à 0.");
        return;
    }

    // Exécution du dépôt via le Backend
    if (currentAccount->deposit(amount)) {
        QMessageBox::information(this, "Succès", "Dépôt réussi !\nNouveau solde : " + currentAccount->getBalanceString());
        ui->detailDisplay->setText(currentAccount->getAccountDetails()); // Rafraîchir l'affichage
        statusBar()->showMessage("Dépôt de " + QString::number(amount, 'f', 2) + " € effectué.");
        ui->amountLineEdit->clear();
    }
}

// --- PARTIE 3.4 & 5 : OPÉRATION DE RETRAIT ---
void MainWindow::onWithdraw()
{
    // Validation : Le compte doit exister
    if (currentAccount == nullptr) {
        QMessageBox::warning(this, "Erreur", "Veuillez d'abord rechercher ou créer un compte.");
        return;
    }

    // Validation : Le montant doit être numérique et positif
    bool ok;
    double amount = ui->amountLineEdit->text().toDouble(&ok);
    if (!ok || amount <= 0) {
        QMessageBox::critical(this, "Erreur de montant", "Veuillez entrer un montant numérique strictement supérieur à 0.");
        return;
    }

    // Exécution du retrait (le backend vérifie automatiquement le solde disponible)
    if (currentAccount->withdraw(amount)) {
        QMessageBox::information(this, "Succès", "Retrait réussi !\nNouveau solde : " + currentAccount->getBalanceString());
        ui->detailDisplay->setText(currentAccount->getAccountDetails()); // Rafraîchir l'affichage
        statusBar()->showMessage("Retrait de " + QString::number(amount, 'f', 2) + " € effectué.");
        ui->amountLineEdit->clear();
    } else {
        // Partie 5 : Erreur si solde insuffisant
        QMessageBox::critical(this, "Fonds insuffisants", "Opération refusée : Solde disponible insuffisant !");
        statusBar()->showMessage("Échec du retrait : solde insuffisant.");
    }
}

// --- PARTIE 3.6 : AFFICHER LES DÉTAILS ---
void MainWindow::onDisplayDetails()
{
    if (currentAccount != nullptr) {
        ui->detailDisplay->setText(currentAccount->getAccountDetails());
        statusBar()->showMessage("Détails mis à jour pour " + currentAccount->getDepositorName());
    } else {
        ui->detailDisplay->setText("Aucun compte sélectionné. Veuillez créer un compte ou effectuer une recherche.");
    }
}

// --- PARTIE 3.7 : RÉINITIALISER L'INTERFACE ---
void MainWindow::onReset()
{
    ui->searchLineEdit->clear();
    ui->searchTypeComboBox->setCurrentIndex(0);
    ui->amountLineEdit->clear();
    ui->detailDisplay->clear();
    currentAccount = nullptr; // Déselectionne le compte en cours
    statusBar()->showMessage("Champs réinitialisés. Les données de comptes sont conservées en mémoire.");
}

// --- PARTIE 3.8 : QUITTER L'APPLICATION ---
void MainWindow::onExit()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Quitter", "Êtes-vous sûr de vouloir fermer l'application ?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        this->close();
    }
}
