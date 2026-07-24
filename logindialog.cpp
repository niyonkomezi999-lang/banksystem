#include "logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , pinLineEdit(new QLineEdit(this))
    , loginButton(new QPushButton("Login", this))
    , cancelButton(new QPushButton("Cancel", this))
{
    setWindowTitle("Bank Authentication");
    setFixedSize(400, 150);
    setModal(true);

    QLabel *titleLabel = new QLabel("Bank Account Management System", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(12);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);

    QLabel *pinLabel = new QLabel("Enter PIN:", this);

    pinLineEdit->setEchoMode(QLineEdit::Password);
    pinLineEdit->setPlaceholderText("Enter your PIN");
    pinLineEdit->setMaxLength(20);
    pinLineEdit->setAlignment(Qt::AlignCenter);
    QFont pinFont = pinLineEdit->font();
    pinFont.setPointSize(14);
    pinLineEdit->setFont(pinFont);

    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addStretch();
    inputLayout->addWidget(pinLabel);
    inputLayout->addWidget(pinLineEdit);
    inputLayout->addStretch();

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(inputLayout);
    mainLayout->addSpacing(15);
    mainLayout->addLayout(buttonLayout);

    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    connect(cancelButton, &QPushButton::clicked, this, &LoginDialog::onCancelClicked);
}

LoginDialog::~LoginDialog()
{
}

QString LoginDialog::getEnteredPin() const
{
    return enteredPin;
}

void LoginDialog::onLoginClicked()
{
    enteredPin = pinLineEdit->text();

    if (enteredPin.isEmpty()) {
        QMessageBox::warning(this, "Authentication Failed", "Please enter a PIN.");
        return;
    }

    accept();
}

void LoginDialog::onCancelClicked()
{
    enteredPin.clear();
    reject();
}
