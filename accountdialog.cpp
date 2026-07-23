#include "accountdialog.h"
#include "ui_accountdialog.h"
#include <QMessageBox>

AccountDialog::AccountDialog(QWidget *parent, bool darkMode)
    : QDialog(parent), ui(new Ui::AccountDialog) {
    ui->setupUi(this);

    if (darkMode) {
        setStyleSheet("QDialog { background-color: #1e1e2e; }"
                      "QLabel { color: #e0e0e0; font: 600 10pt 'Segoe UI'; padding: 4px; }"
                      "QLineEdit { font: 400 10pt 'Segoe UI'; min-height: 34px; padding: 6px 12px; border: 2px solid #555; border-radius: 6px; background-color: #3d3d5c; color: #ffffff; selection-background-color: #bfdbfe; }"
                      "QLineEdit:focus { border: 2px solid #3b82f6; }"
                      "QComboBox { font: 400 10pt 'Segoe UI'; min-height: 34px; padding: 4px 12px; border: 2px solid #555; border-radius: 6px; background-color: #3d3d5c; color: #ffffff; }"
                      "QComboBox:focus { border: 2px solid #3b82f6; }"
                      "QComboBox::drop-down { border: none; width: 30px; }"
                      "QComboBox QAbstractItemView { background-color: #3d3d5c; color: #ffffff; border: 1px solid #555; selection-background-color: #eff6ff; selection-color: #1e40af; }"
                      "QPushButton { font: 600 10pt 'Segoe UI'; min-width: 100px; min-height: 38px; padding: 8px 20px; border-radius: 6px; border: none; }"
                      "#okButton { background-color: #059669; color: #ffffff; }"
                      "#okButton:hover { background-color: #047857; }"
                      "#cancelButton { background-color: #3d3d5c; color: #e0e0e0; border: 2px solid #555; }"
                      "#cancelButton:hover { background-color: #4d4d6c; }");
    }

    connect(ui->okButton, &QPushButton::clicked, this, &AccountDialog::onValidate);
    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

AccountDialog::~AccountDialog() {
    delete ui;
}

void AccountDialog::onValidate() {
    // 1. Validation du Nom (Ne doit pas être vide)
    QString name = ui->nameEdit->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::critical(this, "Erreur de saisie", "Le nom du déposant ne peut pas être vide !");
        return;
    }

    // 2. Validation du Numéro de compte (Doit être un entier positif)
    bool okConvertInt;
    int accNum = ui->accNumEdit->text().toInt(&okConvertInt);
    if (!okConvertInt || accNum <= 0) {
        QMessageBox::critical(this, "Erreur de saisie", "Le numéro de compte doit être un nombre entier positif !");
        return;
    }

    // 3. Validation du PIN (4 chiffres)
    QString pin = ui->pinEdit->text().trimmed();
    if (pin.isEmpty() || pin.length() != 4 || !pin.toInt()) {
        QMessageBox::critical(this, "Erreur de saisie", "Le PIN doit contenir exactement 4 chiffres !");
        return;
    }

    // 4. Validation du Solde initial (Doit être numérique et >= 0)
    bool okConvertDouble;
    double initialBalance = ui->initialBalanceEdit->text().toDouble(&okConvertDouble);
    if (!okConvertDouble || initialBalance < 0) {
        QMessageBox::critical(this, "Erreur de saisie", "Le dépôt initial doit être un nombre supérieur ou égal à 0 !");
        return;
    }

    // 5. Extraction du Type de compte (depuis la ComboBox)
    QString type = ui->typeComboBox->currentText();

    // Si toutes les règles sont respectées, on configure l'objet
    createdAccount.createAccount(name, accNum, type, initialBalance, pin);

    // On ferme le dialogue en renvoyant le code de succès "Accepted"
    accept();
}

BankAccount AccountDialog::getCreatedAccount() const {
    return createdAccount;
}
