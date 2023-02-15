/********************************************************************************
** Form generated from reading UI file 'general_settings.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERAL_SETTINGS_H
#define UI_GENERAL_SETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GeneralSettings
{
public:

    void setupUi(QWidget *GeneralSettings)
    {
        if (GeneralSettings->objectName().isEmpty())
            GeneralSettings->setObjectName("GeneralSettings");
        GeneralSettings->resize(400, 300);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/mainapp/sources/appico.ico"), QSize(), QIcon::Normal, QIcon::Off);
        GeneralSettings->setWindowIcon(icon);

        retranslateUi(GeneralSettings);

        QMetaObject::connectSlotsByName(GeneralSettings);
    } // setupUi

    void retranslateUi(QWidget *GeneralSettings)
    {
        GeneralSettings->setWindowTitle(QCoreApplication::translate("GeneralSettings", "\320\236\320\261\321\211\320\270\320\265 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GeneralSettings: public Ui_GeneralSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERAL_SETTINGS_H
