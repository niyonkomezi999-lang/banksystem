#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include <QDialog>
#include "bankaccount.h" // Nécessaire pour manipuler la classe métier

namespace Ui {
class AccountDialog;
}

class AccountDialog : public QDialog {
    Q_OBJECT

public:
    explicit AccountDialog(QWidget *parent = nullptr);
    ~AccountDialog();

    // Permet à MainWindow de récupérer le compte configuré par l'utilisateur
    BankAccount getCreatedAccount() const;

private slots:
    void onValidate(); // Notre slot personnalisé pour valider les contraintes

private:
    Ui::AccountDialog *ui;
    BankAccount createdAccount; // Stocke temporairement le compte créé
};

#endif // ACCOUNTDIALOG_H
