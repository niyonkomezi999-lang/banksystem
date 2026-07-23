#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H

#include <QMainWindow>
#include <QList>
#include "bankaccount.h"

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
    void onCheckBalance();
    void onDisplayDetails();
    void onReset();
    void onExit();

private:
    Ui::MainWindow *ui;              // Déclare le pointeur d'interface 'ui'
    QList<BankAccount> accountsList;  // Déclare la liste globale des comptes
    BankAccount *currentAccount;      // Déclare le pointeur du compte actif
};

#endif // MAINWINDOWS_H
