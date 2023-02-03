#include "log_in_form.h"
#include "ui_log_in_form.h"
#include "mainwindow.h"
#include <QTimer>

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

LogInForm::LogInForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogInForm)
{
    ui->setupUi(this);
    // Автомасштабирование элементов
    this->timerScale = new QTimer(this);
    connect(timerScale, SIGNAL(timeout()), this, SLOT(autoscale()));
    timerScale->start(1);
}

void LogInForm::autoscale () {
    this->ui->tabWidget->setGeometry(0, 0, this->width(), this->height());

    this->ui->label_login->setGeometry(0, 0, this->width(), 30);
    this->ui->loginField->setGeometry(0, 30, this->width(), 24);

    this->ui->label_password->setGeometry(0, 60, this->width(), 30);
    this->ui->passwordField->setGeometry(0, 90, this->width(), 24);

    this->ui->signInButton->setGeometry((this->width() / 2) - 40, 130, 80, 24);
    this->ui->signInFromFileButton->setGeometry((this->width() / 2) - 50, 170, 100, 24);
}

LogInForm::~LogInForm() {
    delete ui;
}
