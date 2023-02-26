/********************************************************************************
** Form generated from reading UI file 'freenet_settings.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FREENET_SETTINGS_H
#define UI_FREENET_SETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FreenetSettings
{
public:

    void setupUi(QWidget *FreenetSettings)
    {
        if (FreenetSettings->objectName().isEmpty())
            FreenetSettings->setObjectName("FreenetSettings");
        FreenetSettings->resize(400, 300);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/mainapp/sources/freenet.png"), QSize(), QIcon::Normal, QIcon::Off);
        FreenetSettings->setWindowIcon(icon);

        retranslateUi(FreenetSettings);

        QMetaObject::connectSlotsByName(FreenetSettings);
    } // setupUi

    void retranslateUi(QWidget *FreenetSettings)
    {
        FreenetSettings->setWindowTitle(QCoreApplication::translate("FreenetSettings", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 freenet", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FreenetSettings: public Ui_FreenetSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FREENET_SETTINGS_H
