#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <QString>

class BankAccount {
private:
    QString depositorName;
    int accountNumber;
    QString accountType; // "Savings" or "Current"
    double balance;
    QString pin;

public:
    BankAccount();
    void createAccount(QString name, int accNum, QString type, double initialBalance, QString pin);
    
    bool deposit(double amount);
    bool withdraw(double amount);

    // Getters
    QString getDepositorName() const;
    int getAccountNumber() const;
    QString getAccountType() const;
    double getBalance() const;
    QString getPin() const;
    QString getBalanceString() const;
    QString getAccountDetails() const;
    bool verifyPin(const QString &inputPin) const;
};

#endif // BANKACCOUNT_H