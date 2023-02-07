#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "databaseAI.h"
#include "locales.h"
#include <QTimer>
#include <iostream>
#include <QMessageBox>

/*
Уважаемые (и не очень) любители комментариев "на английском языке",
а также уважаемые (и, опять же, не очень) любители #ихборьбы с ненависьтью
обычного русскоговорящего населения (да и русских в частности на каком
языке они бы не общались), которые родились с Российским (или Белорусским
гражданством). Этот код написан гражданином Российской Федерации: русским и на
половину украинцем. Если вам не нравится этот факт, или факт того, что тут
пишут комментарии на русском языке - ищите другие проекты. Если вам нужны
мои комментарии пользуйтесь либо словарём, либо гугл (или яндекс) переводчиком

Приходько Н.С. (FullGreaM) 2023 год
-------------------------------------------------------------------------------
Dear (and not so) fans of comments "in English",
as well as dear (and, again, not so) fans of #cancelculture the non-writing of the
ordinary Russian-speaking population (and Russians in particular in what language
they would not communicate in the language), who were born with Russian (or Belarusian
citizenship). This code is written by a citizen of the Russian Federation: Russian and
half Ukrainian. If you don't like this fact, or the fact that comments are written here
in Russian - look for other projects. If you need my comments either use a dictionary
or Google (or Bing) translator

Prikhodko N.S. (FullGreaM) 2023
*/

MainWindow::MainWindow (QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    //this->database = new DatabaseAppInterface();
    if (this->database.raisedError) {
        QMessageBox messageBox;
        Locales* loc = new Locales(this->locale);
        messageBox.critical(0, QString::fromStdString(loc->getLocaleVar("fio.errorTitle")), QString::fromStdString(loc->getLocaleVar(this->database.dbError)));

        // Закрытие окна
        this->error = true;
    }
    else {
        // Автомасштабирование элементов
        this->timerScale = new QTimer(this);
        connect(timerScale, SIGNAL(timeout()), this, SLOT(autoscale()));
        timerScale->start(1);
        // Запуск таймера по динамическому доступу элементов для пользователя
        this->timerAccess = new QTimer(this);
        connect(timerAccess, SIGNAL(timeout()), this, SLOT(dynamicAccess()));
        timerAccess->start(1);

        // Подключение кнопок
        connect(this->ui->creditsAction, SIGNAL(triggered()), this, SLOT(on_creditsAction_clicked()));
    }
}

void MainWindow::setupLocale (std::string locale) {
    Locales* loc = new Locales(this->locale);
    // Устанавливаем значения согласно ключам
    // Заголовок
    this->setWindowTitle(QString::fromStdString(loc->getLocaleVar("prog.name")));
    // Меню
    // Главные элементы
    this->ui->menu->setTitle(QString::fromStdString(loc->getLocaleVar("menu.mainw.prog")));
    this->ui->menuAccount->setTitle(QString::fromStdString(loc->getLocaleVar("menu.mainw.account")));
    this->ui->menuLanguage->setTitle(QString::fromStdString(loc->getLocaleVar("menu.mainw.language")));
    // Дочерние элементы (выпадающие списки)
    this->ui->logoutMenu->setTitle(QString::fromStdString(loc->getLocaleVar("menu.mainw.logout")));
    this->ui->menuSettings->setTitle(QString::fromStdString(loc->getLocaleVar("menu.mainw.settings")));
    // Дочерние элементы (кнопки)
    this->ui->creditsAction->setText(QString::fromStdString(loc->getLocaleVar("menu.mainw.credits")));
    // Tab-виджеты
    this->ui->tabWidget->setTabText(0, QString::fromStdString(loc->getLocaleVar("prog.tab.profile")));
    this->ui->tabWidget->setTabText(1, QString::fromStdString(loc->getLocaleVar("prog.tab.messages")));
    this->ui->tabWidget->setTabText(2, QString::fromStdString(loc->getLocaleVar("prog.tab.storage")));
    // Текст-лейбелы
    this->ui->label_id->setText(QString::fromStdString(loc->getLocaleVar("labels.mainw.id")));
    this->ui->label_i2padr->setText(QString::fromStdString(loc->getLocaleVar("labels.mainw.i2pAdr")));
    this->ui->label_login->setText(QString::fromStdString(loc->getLocaleVar("labels.mainw.login")));
    this->ui->label_keys->setText(QString::fromStdString(loc->getLocaleVar("labels.mainw.keys")));
    this->ui->label_contacts->setText(QString::fromStdString(loc->getLocaleVar("labels.mainw.contacts")));
    this->ui->label_messages->setText(QString::fromStdString(loc->getLocaleVar("labels.mainw.messages")));
    this->ui->label_dialog->setText(QString::fromStdString(loc->getLocaleVar("labels.mainw.dialog")));
    this->ui->inDevTxt->setText(QString::fromStdString(loc->getLocaleVar("labels.mainw.indev")));
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
    /*logInForm.setupLocale(locale);
    credits.setupLocale(locale);*/
}

MainWindow::~MainWindow () {
    delete ui;
}

int getSize (float startSize, float startCoordValue, float currentCoordValue) {
    return (int)(startSize * (startSize / (startSize * (startCoordValue / currentCoordValue))));
}

void MainWindow::on_creditsAction_clicked () {
    credits.hide();
    credits.show();
}

bool MainWindow::isAuthed () {
    return true;
}

void MainWindow::showLogIn () {
    logInForm.show();
    this->needAuth = true;
}

void MainWindow::dynamicAccess() {
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
    // Автовыход при закрытии окна авторизации
    if (this->needAuth && logInForm.isHidden()) {
        this->hide();
    }
    else if (this->needAuth && this->isHidden()) {
        logInForm.hide();
    }
}

void MainWindow::autoscale () {
    int winX = this->ui->centralwidget->width();
    int winY = this->ui->centralwidget->height();

    const int winXcnst = 800;
    const int winYcnst = 557;

    // Таб бар
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
