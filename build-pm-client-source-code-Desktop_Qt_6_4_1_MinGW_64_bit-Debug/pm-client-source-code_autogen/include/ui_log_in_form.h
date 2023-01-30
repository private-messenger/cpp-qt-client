/********************************************************************************
** Form generated from reading UI file 'log_in_form.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOG_IN_FORM_H
#define UI_LOG_IN_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogInForm
{
public:

    void setupUi(QWidget *LogInForm)
    {
        if (LogInForm->objectName().isEmpty())
            LogInForm->setObjectName("LogInForm");
        LogInForm->resize(400, 300);

        retranslateUi(LogInForm);

        QMetaObject::connectSlotsByName(LogInForm);
    } // setupUi

    void retranslateUi(QWidget *LogInForm)
    {
        LogInForm->setWindowTitle(QCoreApplication::translate("LogInForm", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogInForm: public Ui_LogInForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOG_IN_FORM_H
