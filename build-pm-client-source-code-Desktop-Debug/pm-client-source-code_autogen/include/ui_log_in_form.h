/********************************************************************************
** Form generated from reading UI file 'log_in_form.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOG_IN_FORM_H
#define UI_LOG_IN_FORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogInForm
{
public:
    QTabWidget *tabWidget;
    QWidget *signIn;
    QLineEdit *loginField;
    QLabel *label_login;
    QLabel *label_password;
    QLineEdit *passwordField;
    QPushButton *signInButton;
    QPushButton *signInFromFileButton;
    QWidget *signUp;

    void setupUi(QWidget *LogInForm)
    {
        if (LogInForm->objectName().isEmpty())
            LogInForm->setObjectName("LogInForm");
        LogInForm->resize(400, 300);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/mainapp/sources/appico.ico"), QSize(), QIcon::Normal, QIcon::Off);
        LogInForm->setWindowIcon(icon);
        tabWidget = new QTabWidget(LogInForm);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 400, 300));
        signIn = new QWidget();
        signIn->setObjectName("signIn");
        loginField = new QLineEdit(signIn);
        loginField->setObjectName("loginField");
        loginField->setGeometry(QRect(0, 30, 400, 24));
        label_login = new QLabel(signIn);
        label_login->setObjectName("label_login");
        label_login->setGeometry(QRect(0, 0, 400, 30));
        label_password = new QLabel(signIn);
        label_password->setObjectName("label_password");
        label_password->setGeometry(QRect(0, 60, 400, 30));
        passwordField = new QLineEdit(signIn);
        passwordField->setObjectName("passwordField");
        passwordField->setGeometry(QRect(0, 90, 400, 24));
        passwordField->setEchoMode(QLineEdit::Password);
        signInButton = new QPushButton(signIn);
        signInButton->setObjectName("signInButton");
        signInButton->setGeometry(QRect(160, 130, 80, 24));
        signInFromFileButton = new QPushButton(signIn);
        signInFromFileButton->setObjectName("signInFromFileButton");
        signInFromFileButton->setGeometry(QRect(150, 170, 101, 24));
        tabWidget->addTab(signIn, QString());
        signUp = new QWidget();
        signUp->setObjectName("signUp");
        tabWidget->addTab(signUp, QString());

        retranslateUi(LogInForm);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LogInForm);
    } // setupUi

    void retranslateUi(QWidget *LogInForm)
    {
        LogInForm->setWindowTitle(QCoreApplication::translate("LogInForm", "\320\222\321\205\320\276\320\264", nullptr));
        label_login->setText(QCoreApplication::translate("LogInForm", "<html><head/><body><p align=\"center\">\320\233\320\276\320\263\320\270\320\275</p></body></html>", nullptr));
        label_password->setText(QCoreApplication::translate("LogInForm", "<html><head/><body><p align=\"center\">\320\237\320\260\321\200\320\276\320\273\321\214</p></body></html>", nullptr));
        signInButton->setText(QCoreApplication::translate("LogInForm", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        signInFromFileButton->setText(QCoreApplication::translate("LogInForm", "\320\222\320\276\320\271\321\202\320\270 \321\201 \321\204\320\260\320\271\320\273\320\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(signIn), QCoreApplication::translate("LogInForm", "\320\222\321\205\320\276\320\264", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(signUp), QCoreApplication::translate("LogInForm", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogInForm: public Ui_LogInForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOG_IN_FORM_H
