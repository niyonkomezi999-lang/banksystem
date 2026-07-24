#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

class LoginDialog : public QDialog {
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    QString getEnteredPin() const;

private slots:
    void onLoginClicked();
    void onCancelClicked();

private:
    QLineEdit *pinLineEdit;
    QPushButton *loginButton;
    QPushButton *cancelButton;
    QString enteredPin;
};

#endif // LOGINDIALOG_H
