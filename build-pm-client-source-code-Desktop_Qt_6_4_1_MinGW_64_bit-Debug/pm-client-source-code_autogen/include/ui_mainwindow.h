/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *generalSettingsAction;
    QAction *settingsI2pAction;
    QAction *settingsFreenetAction;
    QAction *logoutNow;
    QAction *logoutLater;
    QAction *ruLocaleAction;
    QAction *enLocaleAction;
    QAction *uaLocaleAction;
    QAction *creditsAction;
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *profileTab;
    QLineEdit *idField;
    QLabel *label_id;
    QLabel *label_login;
    QLineEdit *loginField;
    QListWidget *contactList;
    QLabel *label_contacts;
    QLabel *label_keys;
    QListWidget *keysList;
    QPushButton *setLogin;
    QPushButton *updatePas;
    QPushButton *addContact;
    QPushButton *removeContact;
    QLineEdit *i2pAddressField;
    QLabel *label_i2padr;
    QWidget *messagesTab;
    QLabel *label_messages;
    QListWidget *messagesField;
    QLabel *label_dialog;
    QTextBrowser *dialogField;
    QLineEdit *messageArea;
    QPushButton *sendButton;
    QWidget *storageTab;
    QLabel *inDevTxt;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menuSettings;
    QMenu *logoutMenu;
    QMenu *menuLanguage;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/mainapp/sources/appico.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        generalSettingsAction = new QAction(MainWindow);
        generalSettingsAction->setObjectName("generalSettingsAction");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/mainapp/sources/profile.ico"), QSize(), QIcon::Normal, QIcon::Off);
        generalSettingsAction->setIcon(icon1);
        settingsI2pAction = new QAction(MainWindow);
        settingsI2pAction->setObjectName("settingsI2pAction");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/mainapp/sources/i2p.png"), QSize(), QIcon::Normal, QIcon::Off);
        settingsI2pAction->setIcon(icon2);
        settingsFreenetAction = new QAction(MainWindow);
        settingsFreenetAction->setObjectName("settingsFreenetAction");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/mainapp/sources/freenet.png"), QSize(), QIcon::Normal, QIcon::Off);
        settingsFreenetAction->setIcon(icon3);
        logoutNow = new QAction(MainWindow);
        logoutNow->setObjectName("logoutNow");
        logoutLater = new QAction(MainWindow);
        logoutLater->setObjectName("logoutLater");
        ruLocaleAction = new QAction(MainWindow);
        ruLocaleAction->setObjectName("ruLocaleAction");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/locales/langs/rus.png"), QSize(), QIcon::Normal, QIcon::Off);
        ruLocaleAction->setIcon(icon4);
        enLocaleAction = new QAction(MainWindow);
        enLocaleAction->setObjectName("enLocaleAction");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/locales/langs/eng.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        enLocaleAction->setIcon(icon5);
        uaLocaleAction = new QAction(MainWindow);
        uaLocaleAction->setObjectName("uaLocaleAction");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/locales/langs/ua.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        uaLocaleAction->setIcon(icon6);
        creditsAction = new QAction(MainWindow);
        creditsAction->setObjectName("creditsAction");
        creditsAction->setCheckable(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 791, 551));
        profileTab = new QWidget();
        profileTab->setObjectName("profileTab");
        idField = new QLineEdit(profileTab);
        idField->setObjectName("idField");
        idField->setGeometry(QRect(10, 30, 371, 24));
        idField->setReadOnly(true);
        label_id = new QLabel(profileTab);
        label_id->setObjectName("label_id");
        label_id->setGeometry(QRect(10, 9, 371, 21));
        label_login = new QLabel(profileTab);
        label_login->setObjectName("label_login");
        label_login->setGeometry(QRect(10, 60, 281, 21));
        loginField = new QLineEdit(profileTab);
        loginField->setObjectName("loginField");
        loginField->setGeometry(QRect(10, 80, 281, 24));
        contactList = new QListWidget(profileTab);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/mainapp/sources/contacts.ico"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(contactList);
        __qlistwidgetitem->setIcon(icon7);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(contactList);
        __qlistwidgetitem1->setIcon(icon7);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(contactList);
        __qlistwidgetitem2->setIcon(icon7);
        contactList->setObjectName("contactList");
        contactList->setGeometry(QRect(10, 180, 371, 301));
        label_contacts = new QLabel(profileTab);
        label_contacts->setObjectName("label_contacts");
        label_contacts->setGeometry(QRect(10, 150, 371, 31));
        label_keys = new QLabel(profileTab);
        label_keys->setObjectName("label_keys");
        label_keys->setGeometry(QRect(410, 80, 361, 31));
        keysList = new QListWidget(profileTab);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/mainapp/sources/keys.ico"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(keysList);
        __qlistwidgetitem3->setIcon(icon8);
        QListWidgetItem *__qlistwidgetitem4 = new QListWidgetItem(keysList);
        __qlistwidgetitem4->setIcon(icon8);
        QListWidgetItem *__qlistwidgetitem5 = new QListWidgetItem(keysList);
        __qlistwidgetitem5->setIcon(icon8);
        QListWidgetItem *__qlistwidgetitem6 = new QListWidgetItem(keysList);
        __qlistwidgetitem6->setIcon(icon8);
        QListWidgetItem *__qlistwidgetitem7 = new QListWidgetItem(keysList);
        __qlistwidgetitem7->setIcon(icon8);
        keysList->setObjectName("keysList");
        keysList->setGeometry(QRect(410, 110, 361, 391));
        setLogin = new QPushButton(profileTab);
        setLogin->setObjectName("setLogin");
        setLogin->setGeometry(QRect(300, 80, 80, 24));
        setLogin->setCursor(QCursor(Qt::PointingHandCursor));
        updatePas = new QPushButton(profileTab);
        updatePas->setObjectName("updatePas");
        updatePas->setGeometry(QRect(10, 110, 371, 24));
        updatePas->setCursor(QCursor(Qt::PointingHandCursor));
        addContact = new QPushButton(profileTab);
        addContact->setObjectName("addContact");
        addContact->setGeometry(QRect(10, 490, 80, 24));
        addContact->setCursor(QCursor(Qt::PointingHandCursor));
        removeContact = new QPushButton(profileTab);
        removeContact->setObjectName("removeContact");
        removeContact->setGeometry(QRect(100, 490, 80, 24));
        removeContact->setCursor(QCursor(Qt::PointingHandCursor));
        i2pAddressField = new QLineEdit(profileTab);
        i2pAddressField->setObjectName("i2pAddressField");
        i2pAddressField->setGeometry(QRect(390, 31, 371, 24));
        i2pAddressField->setReadOnly(true);
        label_i2padr = new QLabel(profileTab);
        label_i2padr->setObjectName("label_i2padr");
        label_i2padr->setGeometry(QRect(390, 10, 371, 21));
        tabWidget->addTab(profileTab, icon1, QString());
        messagesTab = new QWidget();
        messagesTab->setObjectName("messagesTab");
        label_messages = new QLabel(messagesTab);
        label_messages->setObjectName("label_messages");
        label_messages->setGeometry(QRect(0, 0, 300, 30));
        messagesField = new QListWidget(messagesTab);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/mainapp/sources/chat.ico"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem8 = new QListWidgetItem(messagesField);
        __qlistwidgetitem8->setIcon(icon9);
        QListWidgetItem *__qlistwidgetitem9 = new QListWidgetItem(messagesField);
        __qlistwidgetitem9->setIcon(icon9);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/mainapp/sources/dialog.ico"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem10 = new QListWidgetItem(messagesField);
        __qlistwidgetitem10->setIcon(icon10);
        messagesField->setObjectName("messagesField");
        messagesField->setGeometry(QRect(0, 30, 300, 491));
        label_dialog = new QLabel(messagesTab);
        label_dialog->setObjectName("label_dialog");
        label_dialog->setGeometry(QRect(310, 0, 471, 30));
        dialogField = new QTextBrowser(messagesTab);
        dialogField->setObjectName("dialogField");
        dialogField->setGeometry(QRect(310, 30, 471, 461));
        messageArea = new QLineEdit(messagesTab);
        messageArea->setObjectName("messageArea");
        messageArea->setGeometry(QRect(310, 490, 391, 24));
        sendButton = new QPushButton(messagesTab);
        sendButton->setObjectName("sendButton");
        sendButton->setGeometry(QRect(700, 490, 80, 24));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/mainapp/sources/messages.ico"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(messagesTab, icon11, QString());
        storageTab = new QWidget();
        storageTab->setObjectName("storageTab");
        inDevTxt = new QLabel(storageTab);
        inDevTxt->setObjectName("inDevTxt");
        inDevTxt->setGeometry(QRect(0, 0, 791, 521));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/mainapp/sources/storage.ico"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(storageTab, icon12, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menuSettings = new QMenu(menu);
        menuSettings->setObjectName("menuSettings");
        logoutMenu = new QMenu(menu);
        logoutMenu->setObjectName("logoutMenu");
        menuLanguage = new QMenu(menubar);
        menuLanguage->setObjectName("menuLanguage");
        menuLanguage->setTearOffEnabled(false);
        menuLanguage->setSeparatorsCollapsible(false);
        menuLanguage->setToolTipsVisible(false);
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menuLanguage->menuAction());
        menu->addAction(menuSettings->menuAction());
        menu->addAction(logoutMenu->menuAction());
        menu->addSeparator();
        menu->addAction(creditsAction);
        menuSettings->addSeparator();
        menuSettings->addAction(generalSettingsAction);
        menuSettings->addAction(settingsI2pAction);
        menuSettings->addAction(settingsFreenetAction);
        logoutMenu->addAction(logoutNow);
        logoutMenu->addAction(logoutLater);
        menuLanguage->addAction(ruLocaleAction);
        menuLanguage->addAction(enLocaleAction);
        menuLanguage->addAction(uaLocaleAction);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\241\320\270\321\201\321\202\320\265\320\274\320\260 \320\277\320\265\321\200\321\201\320\276\320\275\320\260\320\273\320\270\320\267\320\270\321\200\320\276\320\262\320\260\320\275\321\213\321\205 \320\270\320\275\320\264\320\270\320\262\320\270\320\264\321\203\320\260\320\273\321\214\320\275\321\213\321\205 \320\272\320\273\321\216\321\207\320\265\320\271 (\320\241\320\237\320\230\320\232)", nullptr));
        generalSettingsAction->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\321\211\320\270\320\265 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
        settingsI2pAction->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 i2p", nullptr));
        settingsFreenetAction->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 freenet", nullptr));
        logoutNow->setText(QCoreApplication::translate("MainWindow", "\320\241\320\265\320\271\321\207\320\260\321\201", nullptr));
        logoutLater->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\321\202\321\214 \320\262\321\200\320\265\320\274\321\217 \320\260\320\262\321\202\320\276\320\262\321\213\321\205\320\276\320\264\320\260", nullptr));
        ruLocaleAction->setText(QCoreApplication::translate("MainWindow", "\320\240\321\203\321\201\321\201\320\272\320\270\320\271 (Russian)", nullptr));
        enLocaleAction->setText(QCoreApplication::translate("MainWindow", "English (English)", nullptr));
        uaLocaleAction->setText(QCoreApplication::translate("MainWindow", "(\316\262) \320\243\320\272\321\200\320\260\321\227\320\275\321\201\321\214\320\272\320\270\320\271 (Ukrainian)", nullptr));
        creditsAction->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261 \320\260\320\262\321\202\320\276\321\200\320\265", nullptr));
        idField->setText(QCoreApplication::translate("MainWindow", "-bjJ5KYD6X0fo55ko=xBcF-eq/58NoV7qwbvs9VzrGdcvWZ/63yQ6g/s1rtY2dB!WCdPbwYWLPAnKsd7A5dRorUew4jT4Ar88Iu1d1!jk6xG2txDd3GsnxTh0JmoZ0x-f=Dxj34mBUYyTaI9!?q=klW6SLd=SSACl2M=rv7FE7VjIVZBZ3s5SrPMIBDx7aWb1l1UyjdpESHpOY-O6ZH5uu-wsMbXF3jem8NZInp6ex6LvgqSGZ5wXV=LIS!EJdr3", nullptr));
        idField->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\236\321\210\320\270\320\261\320\272\320\260 ID", nullptr));
        label_id->setText(QCoreApplication::translate("MainWindow", "\320\222\320\260\321\210 ID", nullptr));
        label_login->setText(QCoreApplication::translate("MainWindow", "\320\222\320\260\321\210 \320\233\320\276\320\263\320\270\320\275", nullptr));
        loginField->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\320\260\321\210 \320\273\320\276\320\263\320\270\320\275", nullptr));

        const bool __sortingEnabled = contactList->isSortingEnabled();
        contactList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = contactList->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("MainWindow", "username111", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = contactList->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("MainWindow", "paswedfaxsz123", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = contactList->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("MainWindow", "qwerety123", nullptr));
        contactList->setSortingEnabled(__sortingEnabled);

        label_contacts->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">\320\232\320\276\320\275\321\202\320\260\320\272\321\202\321\213</p></body></html>", nullptr));
        label_keys->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">\320\232\320\273\321\216\321\207\320\270</p></body></html>", nullptr));

        const bool __sortingEnabled1 = keysList->isSortingEnabled();
        keysList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem3 = keysList->item(0);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("MainWindow", "\320\237\321\203\320\261\320\273\320\270\321\207\320\275\321\213\320\271 \320\272\320\273\321\216\321\207 \320\260\320\272\320\272\320\260\321\203\320\275\321\202\320\260", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = keysList->item(1);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\262\320\260\321\202\320\275\321\213\320\271 \320\272\320\273\321\216\321\207 \320\260\320\272\320\272\320\260\321\203\320\275\321\202\320\260", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = keysList->item(2);
        ___qlistwidgetitem5->setText(QCoreApplication::translate("MainWindow", "\320\232\320\273\321\216\321\207 \321\207\320\260\321\202\320\260 (123)", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = keysList->item(3);
        ___qlistwidgetitem6->setText(QCoreApplication::translate("MainWindow", "\320\232\320\273\321\216\321\207 \321\207\320\260\321\202\320\260 (\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\207\320\260\321\202\320\260)", nullptr));
        QListWidgetItem *___qlistwidgetitem7 = keysList->item(4);
        ___qlistwidgetitem7->setText(QCoreApplication::translate("MainWindow", "\320\232\320\273\321\216\321\207 \320\264\320\270\320\260\320\273\320\276\320\263\320\260 (username111)", nullptr));
        keysList->setSortingEnabled(__sortingEnabled1);

        setLogin->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        updatePas->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        addContact->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        removeContact->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        i2pAddressField->setText(QCoreApplication::translate("MainWindow", "http://asdasjkshdfkjsdhfjsdhkfkjs.i2p", nullptr));
        i2pAddressField->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\236\321\210\320\270\320\261\320\272\320\260 ID", nullptr));
        label_i2padr->setText(QCoreApplication::translate("MainWindow", "\320\222\320\260\321\210 i2p-\320\260\320\264\321\200\320\265\321\201", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(profileTab), QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\321\204\320\270\320\273\321\214", nullptr));
        label_messages->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">\320\241\320\276\320\276\320\261\321\211\320\265\320\275\320\270\321\217</p></body></html>", nullptr));

        const bool __sortingEnabled2 = messagesField->isSortingEnabled();
        messagesField->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem8 = messagesField->item(0);
        ___qlistwidgetitem8->setText(QCoreApplication::translate("MainWindow", "123", nullptr));
        QListWidgetItem *___qlistwidgetitem9 = messagesField->item(1);
        ___qlistwidgetitem9->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\207\320\260\321\202\320\260", nullptr));
        QListWidgetItem *___qlistwidgetitem10 = messagesField->item(2);
        ___qlistwidgetitem10->setText(QCoreApplication::translate("MainWindow", "username111", nullptr));
        messagesField->setSortingEnabled(__sortingEnabled2);

        label_dialog->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">\320\224\320\270\320\260\320\273\320\276\320\263</p></body></html>", nullptr));
        dialogField->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:7pt; color:#8a8a8a;\">\320\223\320\265\320\275\320\265\321\200\320\260\321\206\320\270\321\217 \320\270 \320\277\320\265\321\200\320\265\320\264\320\260\321\207\320\260 \320\272\320\273\321\216\321\207\320\265\320\271 \320\277\321\200\320\276\321\210\320\273\320\260 \321\203\321\201\320\277\320\265\321\210\320\275\320\276, \320\277\321\200\320\270\321\217\321\202"
                        "\320\275\320\276\320\263\320\276 \320\276\320\261\321\211\320\265\320\275\320\270\321\217!</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:7pt; color:#8a8a8a;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700; color:#aa007f;\">[username111]</span>: \320\237\321\200\320\270\320\262\320\265\321\202</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700; color:#55007f;\">[\320\222\321\213]</span>: \320\224\320\260\321\200\320\276\320\262</p></body></html>", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(messagesTab), QCoreApplication::translate("MainWindow", "\320\241\320\276\320\276\320\261\321\211\320\265\320\275\320\270\321\217", nullptr));
        inDevTxt->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:36pt; font-weight:700; color:#8a8a8a;\">\320\222 \321\200\320\260\320\267\321\200\320\260\320\261\320\276\321\202\320\272\320\265</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(storageTab), QCoreApplication::translate("MainWindow", "\320\245\321\200\320\260\320\275\320\270\320\273\320\270\321\211\320\265", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\260", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
        logoutMenu->setTitle(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\271\321\202\320\270 \320\270\320\267 \321\203\321\207\321\221\321\202\320\275\320\276\320\271 \320\267\320\260\320\277\320\270\321\201\320\270", nullptr));
        menuLanguage->setTitle(QCoreApplication::translate("MainWindow", "\320\257\320\267\321\213\320\272 (Language)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
