#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QList>
#include "bankaccount.h"

class DatabaseManager : public QObject {
    Q_OBJECT

public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    bool openDatabase();
    void closeDatabase();
    bool isDatabaseOpen() const;

    bool loadAccounts(QList<BankAccount> &accounts);
    bool insertAccount(const BankAccount &account);
    bool updateAccount(const BankAccount &account);
    bool accountExists(int accountNumber) const;
    bool addTransaction(int accountNumber, const QString &description);
    bool loadTransactions(QMap<int, QList<QString>> &transactionHistory);
    void initializeDefaultData();

private:
    bool createTable();
    bool createTransactionTable();

    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
