#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <QString>

class BankAccount {
private:
    QString depositorName;
    int accountNumber;
    QString accountType; // "Savings" or "Current"
    double balance;

public:
    BankAccount();
    void createAccount(QString name, int accNum, QString type, double initialBalance);
    
    bool deposit(double amount);
    bool withdraw(double amount);

    // Getters
    QString getDepositorName() const;
    int getAccountNumber() const;
    QString getAccountType() const;
    double getBalance() const;
    QString getBalanceString() const;
    QString getAccountDetails() const;
};

#endif // BANKACCOUNT_H