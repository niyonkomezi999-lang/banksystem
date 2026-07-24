/********************************************************************************
** Form generated from reading UI file 'accountdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNTDIALOG_H
#define UI_ACCOUNTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AccountDialog
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *nameEdit;
    QLabel *label_2;
    QLineEdit *accNumEdit;
    QLabel *label_3;
    QComboBox *typeComboBox;
    QLabel *label_pin;
    QLineEdit *pinEdit;
    QLabel *label_4;
    QLineEdit *initialBalanceEdit;
    QPushButton *cancelButton;
    QPushButton *okButton;

    void setupUi(QDialog *AccountDialog)
    {
        if (AccountDialog->objectName().isEmpty())
            AccountDialog->setObjectName("AccountDialog");
        AccountDialog->resize(500, 360);
        AccountDialog->setMinimumSize(QSize(500, 360));
        AccountDialog->setStyleSheet(QString::fromUtf8("QDialog {\n"
"    background-color: #f8fafc;\n"
"}\n"
"QLabel {\n"
"    font: 600 10pt \"Segoe UI\";\n"
"    color: #374151;\n"
"    padding: 4px;\n"
"}\n"
"QLineEdit {\n"
"    font: 400 10pt \"Segoe UI\";\n"
"    min-height: 34px;\n"
"    padding: 6px 12px;\n"
"    border: 2px solid #d1d5db;\n"
"    border-radius: 6px;\n"
"    background-color: #ffffff;\n"
"    selection-background-color: #bfdbfe;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 2px solid #3b82f6;\n"
"}\n"
"QComboBox {\n"
"    font: 400 10pt \"Segoe UI\";\n"
"    min-height: 34px;\n"
"    padding: 4px 12px;\n"
"    border: 2px solid #d1d5db;\n"
"    border-radius: 6px;\n"
"    background-color: #ffffff;\n"
"}\n"
"QComboBox:focus {\n"
"    border: 2px solid #3b82f6;\n"
"}\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"    width: 30px;\n"
"}\n"
"QComboBox QAbstractItemView {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #e5e7eb;\n"
"    selection-background-color: #eff6ff;\n"
"    selection-color: #1e40af;\n"
"}\n"
"QPushButton "
                        "{\n"
"    font: 600 10pt \"Segoe UI\";\n"
"    min-width: 100px;\n"
"    min-height: 38px;\n"
"    padding: 8px 20px;\n"
"    border-radius: 6px;\n"
"    border: none;\n"
"}\n"
"#okButton {\n"
"    background-color: #059669;\n"
"    color: #ffffff;\n"
"}\n"
"#okButton:hover {\n"
"    background-color: #047857;\n"
"}\n"
"#cancelButton {\n"
"    background-color: #f3f4f6;\n"
"    color: #374151;\n"
"    border: 2px solid #d1d5db;\n"
"}\n"
"#cancelButton:hover {\n"
"    background-color: #e5e7eb;\n"
"}"));
        formLayout = new QFormLayout(AccountDialog);
        formLayout->setSpacing(16);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(32, 32, 32, 32);
        label = new QLabel(AccountDialog);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        nameEdit = new QLineEdit(AccountDialog);
        nameEdit->setObjectName("nameEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, nameEdit);

        label_2 = new QLabel(AccountDialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        accNumEdit = new QLineEdit(AccountDialog);
        accNumEdit->setObjectName("accNumEdit");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, accNumEdit);

        label_3 = new QLabel(AccountDialog);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);

        typeComboBox = new QComboBox(AccountDialog);
        typeComboBox->addItem(QString());
        typeComboBox->addItem(QString());
        typeComboBox->setObjectName("typeComboBox");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, typeComboBox);

        label_pin = new QLabel(AccountDialog);
        label_pin->setObjectName("label_pin");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_pin);

        pinEdit = new QLineEdit(AccountDialog);
        pinEdit->setObjectName("pinEdit");
        pinEdit->setMaxLength(4);
        pinEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, pinEdit);

        label_4 = new QLabel(AccountDialog);
        label_4->setObjectName("label_4");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label_4);

        initialBalanceEdit = new QLineEdit(AccountDialog);
        initialBalanceEdit->setObjectName("initialBalanceEdit");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, initialBalanceEdit);

        cancelButton = new QPushButton(AccountDialog);
        cancelButton->setObjectName("cancelButton");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, cancelButton);

        okButton = new QPushButton(AccountDialog);
        okButton->setObjectName("okButton");

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, okButton);


        retranslateUi(AccountDialog);

        QMetaObject::connectSlotsByName(AccountDialog);
    } // setupUi

    void retranslateUi(QDialog *AccountDialog)
    {
        AccountDialog->setWindowTitle(QCoreApplication::translate("AccountDialog", "Cr\303\251er un nouveau compte", nullptr));
        label->setText(QCoreApplication::translate("AccountDialog", "Nom du d\303\251posant", nullptr));
        nameEdit->setPlaceholderText(QCoreApplication::translate("AccountDialog", "Entrez le nom complet", nullptr));
        label_2->setText(QCoreApplication::translate("AccountDialog", "Num\303\251ro de compte", nullptr));
        accNumEdit->setPlaceholderText(QCoreApplication::translate("AccountDialog", "Ex : 12345", nullptr));
        label_3->setText(QCoreApplication::translate("AccountDialog", "Type de compte", nullptr));
        typeComboBox->setItemText(0, QCoreApplication::translate("AccountDialog", "Savings", nullptr));
        typeComboBox->setItemText(1, QCoreApplication::translate("AccountDialog", "Current", nullptr));

        label_pin->setText(QCoreApplication::translate("AccountDialog", "PIN (4 chiffres)", nullptr));
        pinEdit->setPlaceholderText(QCoreApplication::translate("AccountDialog", "Ex : 1234", nullptr));
        label_4->setText(QCoreApplication::translate("AccountDialog", "D\303\251p\303\264t initial (\342\202\254)", nullptr));
        initialBalanceEdit->setPlaceholderText(QCoreApplication::translate("AccountDialog", "0.00", nullptr));
        cancelButton->setText(QCoreApplication::translate("AccountDialog", "Annuler", nullptr));
        okButton->setText(QCoreApplication::translate("AccountDialog", "Valider", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AccountDialog: public Ui_AccountDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNTDIALOG_H
