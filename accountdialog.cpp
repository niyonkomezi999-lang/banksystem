#include "accountdialog.h"
#include "ui_accountdialog.h"
#include <QMessageBox>

AccountDialog::AccountDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AccountDialog) {
    ui->setupUi(this);

    // Connexion manuelle de nos boutons de validation/annulation
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

    // 3. Validation du Solde initial (Doit être numérique et >= 0)
    bool okConvertDouble;
    double initialBalance = ui->initialBalanceEdit->text().toDouble(&okConvertDouble);
    if (!okConvertDouble || initialBalance < 0) {
        QMessageBox::critical(this, "Erreur de saisie", "Le dépôt initial doit être un nombre supérieur ou égal à 0 !");
        return;
    }

    // 4. Extraction du Type de compte (depuis la ComboBox)
    QString type = ui->typeComboBox->currentText();

    // Si toutes les règles sont respectées, on configure l'objet
    createdAccount.createAccount(name, accNum, type, initialBalance);

    // On ferme le dialogue en renvoyant le code de succès "Accepted"
    accept();
}

BankAccount AccountDialog::getCreatedAccount() const {
    return createdAccount;
}
