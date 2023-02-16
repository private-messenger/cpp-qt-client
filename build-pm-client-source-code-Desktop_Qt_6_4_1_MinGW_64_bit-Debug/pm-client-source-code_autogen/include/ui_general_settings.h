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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GeneralSettings
{
public:
    QCheckBox *checkBox;

    void setupUi(QWidget *GeneralSettings)
    {
        if (GeneralSettings->objectName().isEmpty())
            GeneralSettings->setObjectName("GeneralSettings");
        GeneralSettings->resize(562, 348);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/mainapp/sources/appico.ico"), QSize(), QIcon::Normal, QIcon::Off);
        GeneralSettings->setWindowIcon(icon);
        checkBox = new QCheckBox(GeneralSettings);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(10, 320, 551, 22));
        checkBox->setChecked(true);

        retranslateUi(GeneralSettings);

        QMetaObject::connectSlotsByName(GeneralSettings);
    } // setupUi

    void retranslateUi(QWidget *GeneralSettings)
    {
        GeneralSettings->setWindowTitle(QCoreApplication::translate("GeneralSettings", "\320\236\320\261\321\211\320\270\320\265 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
        checkBox->setText(QCoreApplication::translate("GeneralSettings", "\320\240\320\265\320\266\320\270\320\274 \320\276\321\202\320\273\320\260\320\264\320\272\320\270 (\320\222\320\272\320\273\321\216\321\207\320\260\320\265\321\202 \321\201\320\270\321\201\321\202\320\265\320\274\320\275\321\213\320\265 \320\262\321\213\320\262\320\276\320\264\321\213 \320\270 \320\277\321\200\320\276\321\207\321\203\321\216 \321\201\320\272\321\203\321\207\320\275\321\203\321\216 \321\205\321\200\320\265\320\275\321\214, \320\273\321\203\321\207\321\210\320\265 \320\276\321\202\320\272\320\273\321\216\321\207\320\270\321\202\321\214)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GeneralSettings: public Ui_GeneralSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERAL_SETTINGS_H
