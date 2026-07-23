QT       += core gui widgets

TARGET = BankAccountManagement
TEMPLATE = app

SOURCES += main.cpp\
        accountdialog.cpp \
        mainwindows.cpp\
        bankaccount.cpp

HEADERS  += mainwindows.h\
        accountdialog.h \
        bankaccount.h

FORMS += \
    accountdialog.ui \
    mainwindows.ui
