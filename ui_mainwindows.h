/********************************************************************************
** Form generated from reading UI file 'mainwindows.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWS_H
#define UI_MAINWINDOWS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *searchLineEdit;
    QLabel *label_type;
    QComboBox *searchTypeComboBox;
    QLabel *label_pin;
    QLineEdit *pinLineEdit;
    QPushButton *searchButton;
    QPushButton *clearSearchButton;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *amountLineEdit;
    QLabel *currencyLabel;
    QLabel *label_currency;
    QComboBox *currencyComboBox;
    QSpacerItem *transactionSpacer;
    QPushButton *depositButton;
    QPushButton *withdrawButton;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *createButton;
    QPushButton *displayButton;
    QPushButton *checkBalanceButton;
    QPushButton *resetButton;
    QPushButton *exitButton;
    QGroupBox *groupBox_tools;
    QHBoxLayout *horizontalLayout_tools;
    QPushButton *interestButton;
    QPushButton *darkModeButton;
    QPushButton *exportButton;
    QPushButton *importButton;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *detailDisplay;
    QListWidget *transactionListWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 800);
        MainWindow->setMinimumSize(QSize(900, 800));
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-color: #f5f7fa;\n"
"}\n"
"QGroupBox {\n"
"    font: 700 10pt \"Segoe UI\";\n"
"    border: 2px solid #d1d5db;\n"
"    border-radius: 8px;\n"
"    margin-top: 12px;\n"
"    padding-top: 12px;\n"
"    background-color: #ffffff;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 12px;\n"
"    padding: 0 8px 0 8px;\n"
"    color: #1e3a5f;\n"
"}\n"
"QPushButton {\n"
"    font: 600 10pt \"Segoe UI\";\n"
"    min-width: 100px;\n"
"    min-height: 36px;\n"
"    padding: 6px 16px;\n"
"    border-radius: 6px;\n"
"    border: none;\n"
"}\n"
"QPushButton:hover {\n"
"    filter: brightness(1.1);\n"
"}\n"
"QPushButton:pressed {\n"
"    filter: brightness(0.95);\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #e5e7eb;\n"
"    color: #9ca3af;\n"
"}\n"
"#createButton {\n"
"    background-color: #059669;\n"
"    color: #ffffff;\n"
"}\n"
"#depositButton {\n"
"    background-color: #2563eb;\n"
"    color: #ffffff;\n"
"}\n"
"#withdrawButton {\n"
"    background"
                        "-color: #dc2626;\n"
"    color: #ffffff;\n"
"}\n"
"#searchButton {\n"
"    background-color: #4b5563;\n"
"    color: #ffffff;\n"
"    min-width: 80px;\n"
"}\n"
"#clearSearchButton {\n"
"    background-color: #f3f4f6;\n"
"    color: #374151;\n"
"    border: 2px solid #d1d5db;\n"
"}\n"
"#clearSearchButton:hover {\n"
"    background-color: #e5e7eb;\n"
"}\n"
"#displayButton {\n"
"    background-color: #0891b2;\n"
"    color: #ffffff;\n"
"}\n"
"#checkBalanceButton {\n"
"    background-color: #7c3aed;\n"
"    color: #ffffff;\n"
"}\n"
"#resetButton {\n"
"    background-color: #f59e0b;\n"
"    color: #ffffff;\n"
"}\n"
"#exitButton {\n"
"    background-color: #374151;\n"
"    color: #ffffff;\n"
"}\n"
"#interestButton {\n"
"    background-color: #0891b2;\n"
"    color: #ffffff;\n"
"}\n"
"#darkModeButton {\n"
"    background-color: #7c3aed;\n"
"    color: #ffffff;\n"
"}\n"
"#exportButton {\n"
"    background-color: #059669;\n"
"    color: #ffffff;\n"
"}\n"
"#importButton {\n"
"    background-color: #d97706;\n"
"    color"
                        ": #ffffff;\n"
"}\n"
"QLineEdit {\n"
"    font: 400 10pt \"Segoe UI\";\n"
"    min-height: 32px;\n"
"    padding: 4px 10px;\n"
"    border: 2px solid #d1d5db;\n"
"    border-radius: 6px;\n"
"    background-color: #ffffff;\n"
"    selection-background-color: #bfdbfe;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 2px solid #3b82f6;\n"
"}\n"
"QTextEdit {\n"
"    font: 400 10pt \"Segoe UI\";\n"
"    border: 2px solid #e5e7eb;\n"
"    border-radius: 8px;\n"
"    background-color: #f9fafb;\n"
"    padding: 12px;\n"
"}\n"
"QListWidget {\n"
"    font: 400 10pt \"Segoe UI\";\n"
"    border: 2px solid #e5e7eb;\n"
"    border-radius: 8px;\n"
"    background-color: #f9fafb;\n"
"    padding: 8px;\n"
"}\n"
"QStatusBar {\n"
"    font: 400 9pt \"Segoe UI\";\n"
"    background-color: #1e3a5f;\n"
"    color: #ffffff;\n"
"    padding: 4px 12px;\n"
"}\n"
"QMenuBar {\n"
"    font: 400 9pt \"Segoe UI\";\n"
"    background-color: #ffffff;\n"
"    color: #111827;\n"
"    border-bottom: 1px solid #e5e7eb;\n"
"}\n"
"QLabel {\n"
"    font:"
                        " 400 10pt \"Segoe UI\";\n"
"    color: #4b5563;\n"
"    padding: 2px 4px;\n"
"}\n"
"#currencyLabel {\n"
"    font: 600 10pt \"Segoe UI\";\n"
"    color: #6b7280;\n"
"    padding: 4px 2px;\n"
"}\n"
"QComboBox {\n"
"    font: 400 10pt \"Segoe UI\";\n"
"    min-height: 32px;\n"
"    padding: 4px 10px;\n"
"    border: 2px solid #d1d5db;\n"
"    border-radius: 6px;\n"
"    background-color: #ffffff;\n"
"}\n"
"QComboBox:focus {\n"
"    border: 2px solid #3b82f6;\n"
"}\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"    width: 28px;\n"
"}\n"
"QComboBox QAbstractItemView {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #e5e7eb;\n"
"    selection-background-color: #eff6ff;\n"
"    selection-color: #1e40af;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(16);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(12);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        searchLineEdit = new QLineEdit(groupBox);
        searchLineEdit->setObjectName("searchLineEdit");

        horizontalLayout_2->addWidget(searchLineEdit);

        label_type = new QLabel(groupBox);
        label_type->setObjectName("label_type");

        horizontalLayout_2->addWidget(label_type);

        searchTypeComboBox = new QComboBox(groupBox);
        searchTypeComboBox->addItem(QString());
        searchTypeComboBox->addItem(QString());
        searchTypeComboBox->addItem(QString());
        searchTypeComboBox->setObjectName("searchTypeComboBox");

        horizontalLayout_2->addWidget(searchTypeComboBox);

        label_pin = new QLabel(groupBox);
        label_pin->setObjectName("label_pin");

        horizontalLayout_2->addWidget(label_pin);

        pinLineEdit = new QLineEdit(groupBox);
        pinLineEdit->setObjectName("pinLineEdit");
        pinLineEdit->setMaxLength(4);
        pinLineEdit->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(pinLineEdit);

        searchButton = new QPushButton(groupBox);
        searchButton->setObjectName("searchButton");

        horizontalLayout_2->addWidget(searchButton);

        clearSearchButton = new QPushButton(groupBox);
        clearSearchButton->setObjectName("clearSearchButton");

        horizontalLayout_2->addWidget(clearSearchButton);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setSpacing(14);
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        amountLineEdit = new QLineEdit(groupBox_2);
        amountLineEdit->setObjectName("amountLineEdit");

        horizontalLayout->addWidget(amountLineEdit);

        currencyLabel = new QLabel(groupBox_2);
        currencyLabel->setObjectName("currencyLabel");

        horizontalLayout->addWidget(currencyLabel);

        label_currency = new QLabel(groupBox_2);
        label_currency->setObjectName("label_currency");

        horizontalLayout->addWidget(label_currency);

        currencyComboBox = new QComboBox(groupBox_2);
        currencyComboBox->addItem(QString());
        currencyComboBox->addItem(QString());
        currencyComboBox->addItem(QString());
        currencyComboBox->setObjectName("currencyComboBox");

        horizontalLayout->addWidget(currencyComboBox);

        transactionSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(transactionSpacer);

        depositButton = new QPushButton(groupBox_2);
        depositButton->setObjectName("depositButton");

        horizontalLayout->addWidget(depositButton);

        withdrawButton = new QPushButton(groupBox_2);
        withdrawButton->setObjectName("withdrawButton");

        horizontalLayout->addWidget(withdrawButton);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        horizontalLayout_3 = new QHBoxLayout(groupBox_3);
        horizontalLayout_3->setSpacing(12);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        createButton = new QPushButton(groupBox_3);
        createButton->setObjectName("createButton");

        horizontalLayout_3->addWidget(createButton);

        displayButton = new QPushButton(groupBox_3);
        displayButton->setObjectName("displayButton");

        horizontalLayout_3->addWidget(displayButton);

        checkBalanceButton = new QPushButton(groupBox_3);
        checkBalanceButton->setObjectName("checkBalanceButton");

        horizontalLayout_3->addWidget(checkBalanceButton);

        resetButton = new QPushButton(groupBox_3);
        resetButton->setObjectName("resetButton");

        horizontalLayout_3->addWidget(resetButton);

        exitButton = new QPushButton(groupBox_3);
        exitButton->setObjectName("exitButton");

        horizontalLayout_3->addWidget(exitButton);


        verticalLayout->addWidget(groupBox_3);

        groupBox_tools = new QGroupBox(centralwidget);
        groupBox_tools->setObjectName("groupBox_tools");
        horizontalLayout_tools = new QHBoxLayout(groupBox_tools);
        horizontalLayout_tools->setSpacing(12);
        horizontalLayout_tools->setObjectName("horizontalLayout_tools");
        interestButton = new QPushButton(groupBox_tools);
        interestButton->setObjectName("interestButton");

        horizontalLayout_tools->addWidget(interestButton);

        darkModeButton = new QPushButton(groupBox_tools);
        darkModeButton->setObjectName("darkModeButton");

        horizontalLayout_tools->addWidget(darkModeButton);

        exportButton = new QPushButton(groupBox_tools);
        exportButton->setObjectName("exportButton");

        horizontalLayout_tools->addWidget(exportButton);

        importButton = new QPushButton(groupBox_tools);
        importButton->setObjectName("importButton");

        horizontalLayout_tools->addWidget(importButton);


        verticalLayout->addWidget(groupBox_tools);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName("groupBox_4");
        verticalLayout_2 = new QVBoxLayout(groupBox_4);
        verticalLayout_2->setSpacing(8);
        verticalLayout_2->setObjectName("verticalLayout_2");
        detailDisplay = new QTextEdit(groupBox_4);
        detailDisplay->setObjectName("detailDisplay");
        detailDisplay->setReadOnly(true);

        verticalLayout_2->addWidget(detailDisplay);

        transactionListWidget = new QListWidget(groupBox_4);
        transactionListWidget->setObjectName("transactionListWidget");

        verticalLayout_2->addWidget(transactionListWidget);


        verticalLayout->addWidget(groupBox_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 900, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Bank Account Management System", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Recherche de compte", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Num\303\251ro de compte", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez le num\303\251ro de compte...", nullptr));
        label_type->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        searchTypeComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Tous", nullptr));
        searchTypeComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Savings", nullptr));
        searchTypeComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Current", nullptr));

        label_pin->setText(QCoreApplication::translate("MainWindow", "PIN", nullptr));
        pinLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez le PIN...", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        clearSearchButton->setText(QCoreApplication::translate("MainWindow", "Effacer", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Transactions", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Montant", nullptr));
        amountLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "0.00", nullptr));
        currencyLabel->setText(QCoreApplication::translate("MainWindow", "EUR", nullptr));
        label_currency->setText(QCoreApplication::translate("MainWindow", "Devise", nullptr));
        currencyComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "EUR", nullptr));
        currencyComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "USD", nullptr));
        currencyComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "GBP", nullptr));

        depositButton->setText(QCoreApplication::translate("MainWindow", "D\303\251p\303\264t", nullptr));
        withdrawButton->setText(QCoreApplication::translate("MainWindow", "Retrait", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Actions", nullptr));
        createButton->setText(QCoreApplication::translate("MainWindow", "Cr\303\251er un Compte", nullptr));
        displayButton->setText(QCoreApplication::translate("MainWindow", "Afficher D\303\251tails", nullptr));
        checkBalanceButton->setText(QCoreApplication::translate("MainWindow", "Consulter Solde", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "R\303\251initialiser", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "Quitter", nullptr));
        groupBox_tools->setTitle(QCoreApplication::translate("MainWindow", "Outils avanc\303\251s", nullptr));
        interestButton->setText(QCoreApplication::translate("MainWindow", "Calculer Int\303\251r\303\252ts", nullptr));
        darkModeButton->setText(QCoreApplication::translate("MainWindow", "Mode Sombre", nullptr));
        exportButton->setText(QCoreApplication::translate("MainWindow", "Exporter CSV", nullptr));
        importButton->setText(QCoreApplication::translate("MainWindow", "Importer CSV", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Informations du compte", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWS_H
