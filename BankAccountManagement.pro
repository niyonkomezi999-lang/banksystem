QT        += core gui widgets sql


TARGET = BankAccountManagement
TEMPLATE = app

SOURCES += main.cpp\
        accountdialog.cpp \
        mainwindows.cpp\
        bankaccount.cpp \
        databasemanager.cpp

HEADERS  += mainwindows.h\
        accountdialog.h \
        bankaccount.h \
        databasemanager.h

FORMS += \
    accountdialog.ui \
    mainwindows.ui
