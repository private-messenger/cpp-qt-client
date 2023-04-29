#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "databaseAI.h"
#include "locales.h"
#include "qdatetime.h"
#include "qprocess.h"
#include "qlistwidget.h"
#include "nodejs-run.h"
#include "create-process.h"
#include "send-msg-thread.h"
#include <QTimer>
#include <iostream>
#include <QMessageBox>
#include <QShortcut>
#include <QDir>
#include <QFileDialog>


MainWindow::MainWindow (QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), server(this) {
    ui->setupUi(this);
    this->clearInterface();
    this->messageUpdaterThread = new MessageUpdater("", this);
    if (this->database.raisedError) {
        QMessageBox messageBox;
        Locales* loc = new Locales(this->locale);
        messageBox.critical(0, QString::fromStdString(loc->getLocaleVar("fio.errorTitle")), QString::fromStdString(loc->getLocaleVar(this->database.dbError) + this->database.details));

        // Закрытие окна
        this->error = true;
    }
    else {
        // Передача объектов дочерним окнам
        this->logInForm.setupDatabase(&this->database);
        // Автомасштабирование элементов
        this->timerScale = new QTimer(this);
        connect(timerScale, SIGNAL(timeout()), this, SLOT(autoscale()));
        timerScale->start(1);
        // Запуск таймера по динамическому доступу элементов для пользователя
        this->timerAccess = new QTimer(this);
        connect(timerAccess, SIGNAL(timeout()), this, SLOT(dynamicAccess()));
        timerAccess->start(1);
        // Подключение слотов к потоку/потокам
        connect(this->messageUpdaterThread, SIGNAL(finished()), this, SLOT(onThreadMessagesFinished()));
        // Подключение горячих клавиш
        QShortcut *shortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_R), this);
        connect(shortcut, SIGNAL(activated()), this, SLOT(reloadForm()));
        // Подключение кнопок
        connect(this->ui->creditsAction, SIGNAL(triggered()), this, SLOT(creditsActionClicked()));
        connect(this->ui->settingsFreenetAction, SIGNAL(triggered()), this, SLOT(freenetSettingsClicked()));
        connect(this->ui->settingsI2pAction, SIGNAL(triggered()), this, SLOT(settingsI2pActionClicked()));
        connect(this->ui->logoutNow, SIGNAL(triggered()), this, SLOT(logoutActionClicked()));
        connect(this->ui->generalSettingsAction, SIGNAL(triggered()), this, SLOT(generalSettingsActionClicked()));
        connect(this->ui->saveAccAction, SIGNAL(triggered()), this, SLOT(saveAccountOnFile()));
        // Установка языка
        connect(this->ui->ruLocaleAction, SIGNAL(triggered()), this, SLOT(setupLang_ru_RU()));
        connect(this->ui->enLocaleAction, SIGNAL(triggered()), this, SLOT(setupLang_en_UK()));
        connect(this->ui->plLocaleAction, SIGNAL(triggered()), this, SLOT(setupLang_pl_PL()));
        connect(this->ui->uaLocaleAction, SIGNAL(triggered()), this, SLOT(setupLang_ua_UA()));
        // Запускаем поток
        this->messageUpdaterThread->start();

        if (this->isAuthed()) {
            this->initInterface();
        }
    }
}

void MainWindow::setupLang_ru_RU() {
    this->setupLocale("ru_RU");
    nodejsRun("nodejs_tools/database/set-value.js activeLang ru_RU");
}

void MainWindow::setupLang_en_UK() {
    this->setupLocale(std::string("en_UK"));
    nodejsRun("nodejs_tools/database/set-value.js activeLang en_UK");
}

void MainWindow::setupLang_pl_PL() {
    this->setupLocale("pl_PL");
    nodejsRun("nodejs_tools/database/set-value.js activeLang pl_PL");
}

void MainWindow::setupLang_ua_UA() {
    this->setupLocale("ua_UA");
    nodejsRun("nodejs_tools/database/set-value.js activeLang ua_UA");
}

void MainWindow::saveAccountOnFile () {
    Locales loc(this->locale);
    QMessageBox messageBox;
    messageBox.warning(0, QString::fromStdString(loc.getLocaleVar("core.warning")), QString::fromStdString(loc.getLocaleVar("core.save_file.warning")));
    QString filename = QFileDialog::getSaveFileName(this, QString::fromStdString(loc.getLocaleVar("core.save_file")), QDir::homePath(),  QString::fromStdString(loc.getLocaleVar("core.save_file.extensions")));
    if (!filename.isEmpty()) {
        // сохраняем файл по выбранному пути
        nodejsRun("nodejs_tools/database/save-my-account.js " + filename);
        messageBox.information(0, QString::fromStdString(loc.getLocaleVar("core.success")), QString::fromStdString(loc.getLocaleVar("core.save_file.success")));
    }
}

void MainWindow::reloadForm () {
    this->reloadMessages();
}

void MainWindow::clearInterface () {
    this->ui->contactList->clear();
    this->ui->keysList->clear();
    this->ui->messagesField->clear();
    this->ui->idField->setText("");
    this->ui->loginField->setText("");
    this->ui->i2pAddressField->setText("");
    this->ui->dialogField->setText("");

    this->keys.clear();
    this->contacts.clear();

    this->login = "";
    this->id    = "";
}

void MainWindow::reloadMessages () {
    int selectedRow = this->ui->messagesField->currentRow();
    this->messages.clear();
    this->messageKeys.clear();
    this->ui->messagesField->clear();
    QStringList chats = QString(nodejsRun("nodejs_tools/database/get-my-messages.js").data()).split("<!::>");
    if (chats[0] != QString("null")) for (QString chatString : chats) {
        QStringList chatItems = chatString.split("<:::>");
        int currentItem = 0;
        vector<QString> emptyVector;
        for (QString chatItem : chatItems) {
            if (currentItem == 0) {
                this->messageKeys.push_back(chatItem);
                this->messages[chatItem] = emptyVector;
                QListWidgetItem* item = new QListWidgetItem();
                Locales loc(this->locale);
                item->setText(QString::fromStdString(loc.getLocaleVar("messages.dialog_by")) + chatItem);
                item->setIcon(QIcon(":/mainapp/sources/dialog.ico"));

                this->ui->messagesField->addItem(item);
            }
            else {
                this->messages[chatItems[0]].push_back(chatItem);
            }
            currentItem++;
        }
    }
    if (selectedRow != -1) {
        this->ui->messagesField->setCurrentRow(selectedRow);
        this->on_messagesField_itemClicked(this->ui->messagesField->currentItem());
    }
}

void MainWindow::initInterface () {
    this->clearInterface();
    this->reloadMessages();
    // Преинициализация данных
    QStringList contacts = QString("not-authed").split("|");
    QStringList keys = QString("not-authed").split("<!::>");
    QStringList loginAndId = QString("not-authed").split(":");
    while (
        contacts[0] == QString("not-authed")   ||
        keys[0] == QString("not-authed")       ||
        loginAndId[0] == QString("not-authed")
    ) {
        contacts = QString(nodejsRun("nodejs_tools/database/get-my-contacts.js").data()).split("|");
        keys = QString(nodejsRun("nodejs_tools/database/get-my-keys.js").data()).split("<!::>");
        loginAndId = QString(nodejsRun("nodejs_tools/database/get-my-login-id.js").data()).split(":");
    }

    // Загрузим контакты
    if (contacts[0] != "null") for (QString contactString : contacts) {
        QListWidgetItem* item = new QListWidgetItem();
        item->setText(contactString.split(":")[0]);
        item->setIcon(QIcon(":/mainapp/sources/contacts.ico"));
        this->ui->contactList->addItem(item);

        std::vector<QString> contactItem = {};
        for (QString contactItemElenent : contactString.split(":")) {
            contactItem.push_back(contactItemElenent);
        }
        this->contacts.push_back(contactItem);
    }
    // Загрузим ключи
    for (QString keyString : keys) {
        std::vector<QString> keyItem = {};
        for (QString keyItemElement : keyString.split("<:::>")) {
            keyItem.push_back(keyItemElement);
        }
        this->keys.push_back(keyItem);

        QListWidgetItem* item = new QListWidgetItem();
        item->setText(keyString.split("<:::>")[0]);
        item->setIcon(QIcon(":/mainapp/sources/keys.ico"));
        this->ui->keysList->addItem(item);
    }
    // Загрузим идентификатор и id
    this->id    = loginAndId[0];
    this->login = loginAndId[1];
    this->ui->idField->setText(loginAndId[0]);
    this->ui->loginField->setText(loginAndId[1]);

    // Загрузим i2p адрес пользователя
    this->b32i2paddress = QString(nodejsRun("nodejs_tools/database/get-my-i2p-address.js").data());
    this->ui->i2pAddressField->setText(this->b32i2paddress);
}

void MainWindow::startServer () {
    if (!this->serverRunned) {
        //qDebug("running server..");
        this->server.run();
        this->serverRunned = true;
        //qDebug("server runned!");
    }
    else {
        this->server.restart();
    }
}

void MainWindow::chooseLocale () {
    // ...
    startProcess("setup-lang");
    this->setupLocale("ru_RU");
}

void MainWindow::setupLocale (std::string locale) {
    Locales* loc = new Locales(locale);
    this->locale = locale;
    // Устанавливаем значения согласно ключам
    // Заголовок
    this->setWindowTitle(QString::fromStdString(loc->getLocaleVar("prog.name")));
    // Меню
    // Главные элементы
    this->ui->menu->setTitle(QString::fromStdString(loc->getLocaleVar("menu.mainw.main")));
    this->ui->menuAccount->setTitle(QString::fromStdString(loc->getLocaleVar("menu.mainw.account")));
    this->ui->menuLanguage->setTitle(QString::fromStdString(loc->getLocaleVar("menu.mainw.language") + " (Language)"));
    // Дочерние элементы (выпадающие списки)
    this->ui->logoutMenu->setTitle(QString::fromStdString(loc->getLocaleVar("menu.mainw.logout")));
    this->ui->menuSettings->setTitle(QString::fromStdString(loc->getLocaleVar("menu.mainw.settings")));
    // Дочерние элементы (кнопки)
    this->ui->creditsAction->setText(QString::fromStdString(loc->getLocaleVar("menu.mainw.credits")));

    this->ui->logoutLater->setText(QString::fromStdString(loc->getLocaleVar("menu.mainw.logoutlater")));
    this->ui->logoutNow->setText(QString::fromStdString(loc->getLocaleVar("menu.mainw.logoutnow")));

    this->ui->generalSettingsAction->setText(QString::fromStdString(loc->getLocaleVar("menu.mainw.settings.general")));
    this->ui->settingsI2pAction->setText(QString::fromStdString(loc->getLocaleVar("menu.mainw.settings.i2p")));
    this->ui->settingsFreenetAction->setText(QString::fromStdString(loc->getLocaleVar("menu.mainw.settings.freenet")));

    this->ui->saveAccAction->setText(QString::fromStdString(loc->getLocaleVar("menu.mainw.save")));
    // Tab-виджеты
    this->ui->tabWidget->setTabText(0, QString::fromStdString(loc->getLocaleVar("prog.tab.profile")));
    this->ui->tabWidget->setTabText(1, QString::fromStdString(loc->getLocaleVar("prog.tab.messages")));
    this->ui->tabWidget->setTabText(2, QString::fromStdString(loc->getLocaleVar("prog.tab.storage")));
    // Текст-лейбелы
    this->ui->label_id->setText(QString::fromStdString(loc->getLocaleVar("labels.mainw.id")));
    this->ui->label_i2padr->setText(QString::fromStdString(loc->getLocaleVar("labels.mainw.i2pAdr")));
    this->ui->label_login->setText(QString::fromStdString(loc->getLocaleVar("labels.mainw.login")));
    this->ui->label_keys->setText(QString::fromStdString(loc->getLocaleVar("labels.mainw.keys")));
    this->ui->label_keys->setText("<html><head/><body><p align=\"center\">" + this->ui->label_keys->text() + "</p></body></html>");
    this->ui->label_contacts->setText(QString::fromStdString(loc->getLocaleVar("labels.mainw.contacts")));
    this->ui->label_contacts->setText("<html><head/><body><p align=\"center\">" + this->ui->label_contacts->text() + "</p></body></html>");
    this->ui->label_messages->setText(QString::fromStdString(loc->getLocaleVar("labels.mainw.messages")));
    this->ui->label_messages->setText("<html><head/><body><p align=\"center\">" + this->ui->label_messages->text() + "</p></body></html>");
    this->ui->label_dialog->setText(QString::fromStdString(loc->getLocaleVar("labels.mainw.dialog")));
    this->ui->label_dialog->setText("<html><head/><body><p align=\"center\">" + this->ui->label_dialog->text() + "</p></body></html>");
    this->ui->inDevTxt->setText(QString::fromStdString("<html><head/><body><p align=\"center\"><span style=\" font-size:36pt; font-weight:700; color:#8a8a8a;\">" + loc->getLocaleVar("labels.mainw.indev") + "</span></p></body></html>"));
    // Элементы ввода
    this->ui->idField->setPlaceholderText(QString::fromStdString(loc->getLocaleVar("input.mainw.id")));
    this->ui->i2pAddressField->setPlaceholderText(QString::fromStdString(loc->getLocaleVar("input.mainw.i2pAdr")));
    this->ui->loginField->setPlaceholderText(QString::fromStdString(loc->getLocaleVar("input.mainw.login")));
    // Кнопки
    this->ui->setLogin->setText(QString::fromStdString(loc->getLocaleVar("button.mainw.setlogin")));
    this->ui->updatePas->setText(QString::fromStdString(loc->getLocaleVar("button.mainw.updpassword")));
    this->ui->addContact->setText(QString::fromStdString(loc->getLocaleVar("button.mainw.addcontact")));
    this->ui->removeContact->setText(QString::fromStdString(loc->getLocaleVar("button.mainw.rmcontact")));
    this->ui->sendButton->setText(QString::fromStdString(loc->getLocaleVar("button.mainw.sendmsg")));
    // Установка локализации в дочерние окна
    logInForm.setupLocale(locale);
    credits.setupLocale(locale);
    freenetSettings.setupLocale(locale);
    i2pSettings.setupLocale(locale);
    keyViewer.setupLocale(locale);
    generalSettings.setupLocale(locale);
    addContact.setupLocale(locale);
    // Перезагрузка формы
    if (this->isAuthed())this->initInterface();
}

MainWindow::~MainWindow () {
    delete ui;
    delete this->messageUpdaterThread;
}

int getSize (float startSize, float startCoordValue, float currentCoordValue) {
    return (int)(startSize * (startSize / (startSize * (startCoordValue / currentCoordValue))));
}

void MainWindow::creditsActionClicked () {
    credits.hide();
    credits.show();
}

void MainWindow::logoutActionClicked () {
    QString result = QString(nodejsRun("nodejs_tools/database/logout-now.js").data());
    if (result == QString("ok")) {
        logInForm.isSuccess = false;
        this->needAuth = true;
        this->setDisabled(true);
        this->showLogIn();
        this->clearInterface();
    }
    else {
        Locales* loc = new Locales(this->locale);
        QMessageBox messageBox;
        messageBox.critical(0, QString::fromStdString(loc->getLocaleVar("core.error")), QString::fromStdString(loc->getLocaleVar("core.errorMsg") + result.toStdString().data()));
    }
}

void MainWindow::settingsI2pActionClicked () {
    i2pSettings.hide();
    i2pSettings.show();
}

void MainWindow::freenetSettingsClicked () {
    freenetSettings.hide();
    freenetSettings.show();
}

bool MainWindow::isAuthed () {
    //return true;
    return database.getAuthed();
}

void MainWindow::showLogIn () {
    logInForm.show();
    this->needAuth = true;
}

void MainWindow::dynamicAccess() {
    if (createChat.code != 0) {
        if (createChat.code == 1) this->reloadMessages();
        createChat.code = 0;
    }

    if (this->ui->contactList->currentRow() == -1 && this->ui->removeContact->isEnabled()) {
        this->ui->removeContact->setEnabled(false);
    }
    else if (this->ui->contactList->currentRow() != -1 && this->ui->removeContact->isEnabled() == false) {
        this->ui->removeContact->setEnabled(true);
    }
    // Блокирование окна основной программы (PS: В будущих апдейтах убрать, делаю только для того, чтобы удовлетворить требования крусового проекта)
    if ((credits.isHidden() && logInForm.isHidden()) && !this->isEnabled()) {
        this->setEnabled(true);
    }
    else if ((!credits.isHidden() || !logInForm.isHidden()) && this->isEnabled()) {
        this->setEnabled(false);
    }
    // Автовыход при закрытии окна авторизации и закртие дочерних окон при выходе из основного
    if (logInForm.isSuccess && this->needAuth) {  // Тут парсим состояние окна авторизации
        this->needAuth = false;
        this->initInterface();
        this->startServer();
    }

    if (this->needAuth && logInForm.isHidden()) {
        this->hide();
    }
    else if (this->needAuth && this->isHidden()) {
        logInForm.hide();
    }

    else if (this->needSetupLocale) {
        this->hide();
    }

    else if (!credits.isHidden() && this->isHidden()) {
        credits.hide();
    }
    // Динамический поиск ошибок базы данных
    if (this->database.raisedError) {
        QMessageBox messageBox;
        Locales* loc = new Locales(this->locale);
        messageBox.critical(0, QString::fromStdString(loc->getLocaleVar("fio.errorTitle")), QString::fromStdString(loc->getLocaleVar(this->database.dbError) + this->database.details));

        // Закрытие окна
        this->error = true;
        this->hide();
        QCoreApplication::exit();
    }
    // Автоматическое завершение программы при закрытии главного окна.
    if (this->isHidden()) {
        !this->error ? QCoreApplication::quit() : QCoreApplication::exit();
    }
    // Автообновление при добавлении контакта
    if (this->addContact.updated) {
        this->addContact.updated = false;
        this->initInterface();
    }
    // Обновим при изменениях в сообщениях
    if (this->messageUpdaterThread->messageEdited || QDateTime::currentDateTimeUtc().toSecsSinceEpoch() - this->lastTimeUpdated >= 15) {
        this->reloadMessages();
        this->lastTimeUpdated = QDateTime::currentDateTimeUtc().toSecsSinceEpoch();
        //this->messageUpdaterThread->messageEdited = false;
    }
    // Автоблокировка кнопки
    if (this->ui->sendButton->isEnabled() && (
        this->ui->messageArea->text() == "" ||
        this->ui->messagesField->currentRow() == -1
    )) {
        this->ui->sendButton->setEnabled(false);
    }
    else if (!this->ui->sendButton->isEnabled() && (
        this->ui->messageArea->text() != "" &&
        this->ui->messagesField->currentRow() != -1
    )) {
        this->ui->sendButton->setEnabled(true);
    }
}

void MainWindow::autoscale () {
    int winX = this->ui->centralwidget->width();
    int winY = this->ui->centralwidget->height();

    const int winXcnst = 800;
    const int winYcnst = 557;

    // Профиль
    this->ui->tabWidget->setGeometry(
        0, 0,
        getSize(791, winXcnst, winX), getSize(551, winYcnst, winY)
    );
    this->ui->idField->setGeometry(
        10, 30,
        getSize(371, winXcnst, winX), 24
    );
    this->ui->i2pAddressField->setGeometry(getSize(371, winXcnst, winX) + 19, 30, getSize(371, winXcnst, winX), 24);
    this->ui->label_i2padr->setGeometry(getSize(371, winXcnst, winX) + 19, 10, getSize(371, winXcnst, winX), 21);
    this->ui->label_id->setGeometry(10, 9, getSize(371, winXcnst, winX), 21);
    this->ui->label_login->setGeometry(10, 60, getSize(281, winXcnst, winX), 21);
    this->ui->loginField->setGeometry(10, 80, getSize(281, winXcnst, winX), 24);
    this->ui->setLogin->setGeometry(getSize(281, winXcnst, winX) + 19, 80, 80, 24);
    this->ui->label_keys->setGeometry(getSize(410, winXcnst, winX), 80, getSize(361, winXcnst, winX), 31);
    this->ui->updatePas->setGeometry(10, 110, this->ui->loginField->width() + 9 + this->ui->setLogin->width(), 24);
    this->ui->keysList->setGeometry(getSize(410, winXcnst, winX), 110, this->ui->label_keys->width(), getSize(391, winYcnst, winY));
    this->ui->label_contacts->setGeometry(10, 150, this->ui->updatePas->width(), 31);
    this->ui->contactList->setGeometry(10, 180, this->ui->updatePas->width(), getSize(301, winYcnst, winY));
    this->ui->addContact->setGeometry(10, this->ui->contactList->height() + 189, 80, 24);
    this->ui->removeContact->setGeometry(100, this->ui->contactList->height() + 189, 80, 24);

    // Сообщения
    this->ui->label_messages->setGeometry(0, 0, getSize(300, winXcnst, winX), 30);
    this->ui->messagesField->setGeometry(0, 30, this->ui->label_messages->width(), getSize(491, winYcnst, winY));
    this->ui->dialogField->setGeometry(this->ui->messagesField->width() + 9, 30, getSize(471, winXcnst, winX), this->ui->messagesField->height() - 30);
    this->ui->label_dialog->setGeometry(this->ui->label_messages->width(), 0, this->ui->dialogField->width(), 30);
    this->ui->messageArea->setGeometry(this->ui->dialogField->x(), this->ui->label_dialog->height() + this->ui->dialogField->height(), this->ui->dialogField->width() - 80, 24);
    this->ui->sendButton->setGeometry(this->ui->messageArea->x() + this->ui->messageArea->width(), this->ui->messageArea->y(), 80, 24);
    // Хранилище
    this->ui->inDevTxt->setGeometry(
        0, 0,
        getSize(791, winXcnst, winX),
        getSize(521, winYcnst, winY)
    );
}

void MainWindow::onThreadMessagesFinished () {
    //qDebug(this->messageUpdaterThread->messageEdited ? "this->messageUpdaterThread.messageEdited: 1" : "this->messageUpdaterThread.messageEdited: 0");
    /*if (this->messageUpdaterThread->messageEdited) {
        this->reloadMessages();
    }*/
    this->messageUpdaterThread->start();
}

void MainWindow::on_keysList_itemDoubleClicked (QListWidgetItem *item) {
    keyViewer.hide();
    int id = this->ui->keysList->currentRow();
    keyViewer.setData(this->keys.at(id));
    keyViewer.show();
    //qDebug(this->keys.at(id)[0].toStdString().c_str());
}

void MainWindow::generalSettingsActionClicked () {
    generalSettings.hide();
    generalSettings.setEnabled(false);

    QMessageBox messagebox;
    Locales loc(this->locale);
    messagebox.warning(0, QString::fromStdString(loc.getLocaleVar("core.in_progress.title")), QString::fromStdString(loc.getLocaleVar("core.in_progress.msg")));
    //generalSettings.show();
}

void MainWindow::on_contactList_itemDoubleClicked (QListWidgetItem *item) {
    createChat.hide();
    int id = this->ui->contactList->currentRow();
    createChat.setupData(this->contacts.at(id), this->locale);
    createChat.show();
}


void MainWindow::on_addContact_clicked () {
    addContact.hide();
    addContact.show();
}


void MainWindow::on_updatePas_clicked() {
    QMessageBox messagebox;
    Locales loc(this->locale);
    messagebox.warning(0, QString::fromStdString(loc.getLocaleVar("core.in_progress.title")), QString::fromStdString(loc.getLocaleVar("core.in_progress.msg")));
}


void MainWindow::on_messagesField_itemClicked(QListWidgetItem *item) {
    Locales loc(this->locale);
    QString selectedChatId = this->messageKeys[this->ui->messagesField->currentRow()];
    QString chatArea = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html>\n\n<head>\n	<meta name=\"qrichtext\" content=\"1\" />\n	<meta charset=\"utf-8\" />\n	<style type=\"text/css\">\n	p,\n	li {\n		white-space: pre-wrap;\n	}\n	\n	hr {\n		height: 1px;\n		border-width: 0;\n	}\n	\n	li.unchecked::marker {\n		content: \"\\\\2610\";\n	}\n	\n	li.checked::marker {\n		content: \"\\\\2612\";\n	}\n	\n	\n	</style>\n</head>\n\n<body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n	<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:7pt; color:#8a8a8a;\">"+ QString::fromStdString(loc.getLocaleVar("messages.key_generated")) +"</span></p>\n	<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:7pt; color:#8a8a8a;\">\n		<br />\n	</p>\n";
    for (QString message : this->messages[selectedChatId]) {
        if (QString(message[0]) == QString("<")) {
            chatArea += "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700; color:#55007f;\">["+ QString::fromStdString(loc.getLocaleVar("messages.you")) +"]</span>: "+ message.sliced(1, message.length() - 1) +"</p>\n";
        }
        else if (QString(message[0]) == QString("^")) {
            chatArea += "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700; color:#707070;\">["+ QString::fromStdString(loc.getLocaleVar("messages.you")) +"]</span>: "+ message.sliced(1, message.length() - 1) +"</p>\n";
        }
        else {
            chatArea += "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700; color:#aa007f;\">["+ QString(message.split(">")[0]) +"]</span>: "+ message.split(">").sliced(1, message.split(">").length() - 1).join(">") +"</p>\n";
        }
    }
    chatArea += "</body>\n\n</html>";
    this->ui->dialogField->setHtml(chatArea);
}


void MainWindow::on_sendButton_clicked() {
    Locales loc(this->locale);
    QString selectedChatId = this->messageKeys[this->ui->messagesField->currentRow()];
    this->messages[selectedChatId].push_back(QString("^") + this->ui->messageArea->text());
    //nodejsRun("nodejs_tools/requests/new-message.js " + selectedChatId + " " + this->ui->messageArea->text());
    SendMsgThread* sendThread = new SendMsgThread(selectedChatId + " " + this->ui->messageArea->text(), this);
    sendThread->start();
    this->ui->messageArea->setText("");
    QString chatArea = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html>\n\n<head>\n	<meta name=\"qrichtext\" content=\"1\" />\n	<meta charset=\"utf-8\" />\n	<style type=\"text/css\">\n	p,\n	li {\n		white-space: pre-wrap;\n	}\n	\n	hr {\n		height: 1px;\n		border-width: 0;\n	}\n	\n	li.unchecked::marker {\n		content: \"\\\\2610\";\n	}\n	\n	li.checked::marker {\n		content: \"\\\\2612\";\n	}\n	\n	\n	</style>\n</head>\n\n<body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n	<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:7pt; color:#8a8a8a;\">"+ QString::fromStdString(loc.getLocaleVar("messages.key_generated")) +"</span></p>\n	<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:7pt; color:#8a8a8a;\">\n		<br />\n	</p>\n";
    for (QString message : this->messages[selectedChatId]) {
        if (QString(message[0]) == QString("<")) {
            chatArea += "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700; color:#55007f;\">["+ QString::fromStdString(loc.getLocaleVar("messages.you")) +"]</span>: "+ message.sliced(1, message.length() - 1) +"</p>\n";
        }
        else if (QString(message[0]) == QString("^")) {
            chatArea += "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700; color:#707070;\">["+ QString::fromStdString(loc.getLocaleVar("messages.you")) +"]</span>: "+ message.sliced(1, message.length() - 1) +"</p>\n";
        }
        else {
            chatArea += "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700; color:#aa007f;\">["+ QString(message.split(">")[0]) +"]</span>: "+ message.split(">").sliced(1, message.split(">").length() - 1).join(">") +"</p>\n";
        }
    }
    chatArea += "</body>\n\n</html>";
    this->ui->dialogField->setHtml(chatArea);
}

void MainWindow::on_removeContact_clicked() {
    if (this->ui->contactList->currentRow() != -1) {
        QString contactId = this->contacts.at(this->ui->contactList->currentRow()).at(1);
        nodejsRun("nodejs_tools/database/remove-contact.js " + contactId);
        this->initInterface();
    }
}


void MainWindow::on_setLogin_clicked() {
    QMessageBox messagebox;
    Locales loc(this->locale);
    messagebox.warning(0, QString::fromStdString(loc.getLocaleVar("core.in_progress.title")), QString::fromStdString(loc.getLocaleVar("core.in_progress.msg")));

}

