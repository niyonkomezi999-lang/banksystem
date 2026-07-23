#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H

#include <QMainWindow>
#include <QList>
#include <QMap>
#include <QMessageBox>
#include "bankaccount.h"
#include "databasemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Déclaration des slots de traitement
    void onCreateAccount();
    void onDeposit();
    void onWithdraw();
    void onSearchAccount();
    void onClearSearch();
    bool verifyAccountPin(int accountNumber, const QString &inputPin);
    void onCheckBalance();
    void onDisplayDetails();
    void onReset();
    void onExit();
    void onCalculateInterest();
    void onToggleDarkMode();
    void onExportCSV();
    void onImportCSV();
    void onCurrencyChanged(int index);
    void updateTransactionDisplay();
    void styleMessageBox(QMessageBox *msgBox) const;

private:
    Ui::MainWindow *ui;              // Déclare le pointeur d'interface 'ui'
    QList<BankAccount> accountsList;  // Déclare la liste globale des comptes
    BankAccount *currentAccount;      // Déclare le pointeur du compte actif
    DatabaseManager *dbManager;       // Gestionnaire de base de données SQL
    bool isDarkMode;                  // État du mode sombre
    QMap<int, QList<QString>> transactionHistory; // Historique des transactions par compte
};

#endif // MAINWINDOWS_H
