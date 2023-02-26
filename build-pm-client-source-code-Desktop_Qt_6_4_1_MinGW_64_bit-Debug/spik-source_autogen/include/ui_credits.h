/********************************************************************************
** Form generated from reading UI file 'credits.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREDITS_H
#define UI_CREDITS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Credits
{
public:
    QLabel *label;

    void setupUi(QWidget *Credits)
    {
        if (Credits->objectName().isEmpty())
            Credits->setObjectName("Credits");
        Credits->resize(295, 295);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/mainapp/sources/appico.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Credits->setWindowIcon(icon);
        label = new QLabel(Credits);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 295, 295));

        retranslateUi(Credits);

        QMetaObject::connectSlotsByName(Credits);
    } // setupUi

    void retranslateUi(QWidget *Credits)
    {
        Credits->setWindowTitle(QCoreApplication::translate("Credits", "\320\236\320\261 \320\260\320\262\321\202\320\276\321\200\320\265", nullptr));
        label->setText(QCoreApplication::translate("Credits", "<html><head/><body><p align=\"center\"><img src=\":/mainapp/sources/FullGreaM_avatar.png\" width=\"200\" height=\"200\"/></p><p align=\"center\">\320\240\320\260\320\267\321\200\320\260\320\261\320\276\321\202\321\207\320\270\320\272: \320\237\321\200\320\270\321\205\320\276\320\264\321\214\320\272\320\276 'FullGreaM' \320\235\320\270\320\272\320\270\321\202\320\260<br/>GitHub: https://github.com/Nikiroy78<br/>(c) FullGreaM 2023, \320\273\320\270\321\206\320\265\320\275\320\267\320\270\321\217 MIT</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Credits: public Ui_Credits {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREDITS_H
