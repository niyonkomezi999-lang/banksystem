#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent) {}

DatabaseManager::~DatabaseManager() {
    closeDatabase();
}

bool DatabaseManager::openDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("bank_accounts.db");

    if (!db.open()) {
        qDebug() << "Error: Could not open database:" << db.lastError().text();
        return false;
    }

    if (!createTable()) return false;
    if (!createTransactionTable()) return false;

    return true;
}

void DatabaseManager::closeDatabase() {
    if (db.isOpen()) {
        db.close();
    }
}

bool DatabaseManager::isDatabaseOpen() const {
    return db.isOpen();
}

bool DatabaseManager::createTable() {
    QSqlQuery query;
    QString sql = "CREATE TABLE IF NOT EXISTS accounts ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "depositor_name TEXT NOT NULL, "
                  "account_number INTEGER UNIQUE NOT NULL, "
                  "account_type TEXT NOT NULL, "
                  "balance REAL NOT NULL, "
                  "pin TEXT NOT NULL)";

    if (!query.exec(sql)) {
        qDebug() << "Error creating table:" << query.lastError().text();
        return false;
    }

    QSqlQuery pragma;
    if (!pragma.exec("PRAGMA table_info(accounts)")) {
        qDebug() << "Error checking table schema:" << pragma.lastError().text();
        return false;
    }

    bool hasPin = false;
    while (pragma.next()) {
        if (pragma.value(1).toString() == "pin") {
            hasPin = true;
            break;
        }
    }

    if (!hasPin) {
        QSqlQuery alter;
        if (!alter.exec("ALTER TABLE accounts ADD COLUMN pin TEXT NOT NULL DEFAULT '0000'")) {
            qDebug() << "Error adding pin column:" << alter.lastError().text();
            return false;
        }
    }

    return true;
}

bool DatabaseManager::createTransactionTable() {
    QSqlQuery query;
    QString sql = "CREATE TABLE IF NOT EXISTS transactions ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "account_number INTEGER NOT NULL, "
                  "description TEXT NOT NULL, "
                  "created_at TEXT NOT NULL, "
                  "FOREIGN KEY(account_number) REFERENCES accounts(account_number))";

    if (!query.exec(sql)) {
        qDebug() << "Error creating transactions table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::addTransaction(int accountNumber, const QString &description) {
    if (!db.isOpen() && !db.open()) {
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO transactions (account_number, description, created_at) "
                  "VALUES (?, ?, ?)");
    query.addBindValue(accountNumber);
    query.addBindValue(description);
    query.addBindValue(QDateTime::currentDateTime().toString(Qt::ISODate));

    if (!query.exec()) {
        qDebug() << "Error inserting transaction:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::loadTransactions(QMap<int, QList<QString>> &transactionHistory) {
    transactionHistory.clear();

    if (!db.isOpen() && !db.open()) {
        return false;
    }

    QSqlQuery query("SELECT account_number, description, created_at FROM transactions ORDER BY created_at ASC");

    while (query.next()) {
        int accNum = query.value(0).toInt();
        QString description = query.value(1).toString();
        QString createdAt = query.value(2).toString();

        transactionHistory[accNum].append(description + " | " + createdAt);
    }

    return true;
}

void DatabaseManager::initializeDefaultData() {
}

bool DatabaseManager::loadAccounts(QList<BankAccount> &accounts) {
    accounts.clear();
    QSqlQuery query("SELECT depositor_name, account_number, account_type, balance, pin FROM accounts ORDER BY account_number ASC");

    while (query.next()) {
        BankAccount acc;
        acc.createAccount(
            query.value(0).toString(),
            query.value(1).toInt(),
            query.value(2).toString(),
            query.value(3).toDouble(),
            query.value(4).toString()
        );
        accounts.append(acc);
    }
    return true;
}

bool DatabaseManager::insertAccount(const BankAccount &account) {
    QSqlQuery query;
    query.prepare("INSERT INTO accounts (depositor_name, account_number, account_type, balance, pin) "
                  "VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(account.getDepositorName());
    query.addBindValue(account.getAccountNumber());
    query.addBindValue(account.getAccountType());
    query.addBindValue(account.getBalance());
    query.addBindValue(account.getPin());

    if (!query.exec()) {
        qDebug() << "Error inserting account:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::updateAccount(const BankAccount &account) {
    QSqlQuery query;
    query.prepare("UPDATE accounts SET balance = ? WHERE account_number = ?");
    query.addBindValue(account.getBalance());
    query.addBindValue(account.getAccountNumber());

    if (!query.exec()) {
        qDebug() << "Error updating account:" << query.lastError().text();
        return false;
    }
    return query.numRowsAffected() > 0;
}

bool DatabaseManager::accountExists(int accountNumber) const {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM accounts WHERE account_number = ?");
    query.addBindValue(accountNumber);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}
