#include "bankaccount.h"

BankAccount::BankAccount() 
    : depositorName(""), accountNumber(0), accountType(""), balance(0.0) {}

void BankAccount::createAccount(QString name, int accNum, QString type, double initialBalance) {
    depositorName = name;
    accountNumber = accNum;
    accountType = type;
    balance = initialBalance;
}

bool BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        return true;
    }
    return false;
}

bool BankAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}

QString BankAccount::getDepositorName() const { return depositorName; }
int BankAccount::getAccountNumber() const { return accountNumber; }
QString BankAccount::getAccountType() const { return accountType; }
double BankAccount::getBalance() const { return balance; }

QString BankAccount::getBalanceString() const {
    return QString::number(balance, 'f', 2) + " €";
}

QString BankAccount::getAccountDetails() const {
    return QString("<b>Account Number:</b> %1<br>"
                   "<b>Account Holder:</b> %2<br>"
                   "<b>Account Type:</b> %3<br>"
                   "<b>Current Balance:</b> %4")
            .arg(accountNumber)
            .arg(depositorName)
            .arg(accountType)
            .arg(getBalanceString());
}