#include <QApplication>
#include "mainwindows.h"
#include "logindialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    LoginDialog loginDialog;
    if (loginDialog.exec() == QDialog::Accepted) {
        QString enteredPin = loginDialog.getEnteredPin();

        const QString CORRECT_PIN = "1234";

        if (enteredPin != CORRECT_PIN) {
            QMessageBox::critical(nullptr, "Authentication Failed",
                                  "Invalid PIN. Access denied.");
            return 0;
        }

        MainWindow window;
        window.show();

        return app.exec();
    }

    return 0;
}