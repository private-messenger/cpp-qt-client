/********************************************************************************
** Form generated from reading UI file 'i2p_settings.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_I2P_SETTINGS_H
#define UI_I2P_SETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_I2pSettings
{
public:

    void setupUi(QWidget *I2pSettings)
    {
        if (I2pSettings->objectName().isEmpty())
            I2pSettings->setObjectName("I2pSettings");
        I2pSettings->resize(400, 300);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/mainapp/sources/i2p.png"), QSize(), QIcon::Normal, QIcon::Off);
        I2pSettings->setWindowIcon(icon);

        retranslateUi(I2pSettings);

        QMetaObject::connectSlotsByName(I2pSettings);
    } // setupUi

    void retranslateUi(QWidget *I2pSettings)
    {
        I2pSettings->setWindowTitle(QCoreApplication::translate("I2pSettings", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 i2p", nullptr));
    } // retranslateUi

};

namespace Ui {
    class I2pSettings: public Ui_I2pSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_I2P_SETTINGS_H
