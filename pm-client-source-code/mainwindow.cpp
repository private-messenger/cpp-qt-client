#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTimer>
#include <iostream>

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
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(autoscale()));
    timer->start(1);  // И запустим таймер

    connect(this->ui->creditsAction, SIGNAL(triggered()), this, SLOT(on_creditsAction_clicked()));
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
    // Хранилище
    this->ui->inDevTxt->setGeometry(
        0, 0,
        getSize(791, winXcnst, winX),
        getSize(521, winYcnst, winY)
    );
}
