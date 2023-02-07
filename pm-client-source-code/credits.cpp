#include "credits.h"
#include "ui_credits.h"
#include "locales.h"
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

Credits::Credits(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Credits)
{
    ui->setupUi(this);

    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(autoscale()));
    timer->start(1);  // И запустим таймер
}

void Credits::setupLocale (std::string locale) {
    Locales* loc = new Locales(locale);
    this->setWindowTitle(QString::fromStdString(loc->getLocaleVar("credits.title")));
    //QString developedBy = "Разработчик: ";
    QString developedBy = QString::fromStdString(loc->getLocaleVar("credits.developed_by"));
    QString devLastname = QString::fromStdString(loc->getLocaleVar("credits.developer_lname"));
    QString devName = QString::fromStdString(loc->getLocaleVar("credits.developer_fname"));
    QString mitLicense = QString::fromStdString(loc->getLocaleVar("credits.mit_license"));
    this->ui->label->setText("<html><head/><body><p align=\"center\"><img src=\":/mainapp/sources/FullGreaM_avatar.png\" width=\"200\" height=\"200\"/></p><p align=\"center\">" + developedBy + devLastname + " 'FullGreaM' " + devName + "<br/>GitHub: https://github.com/Nikiroy78<br/>(c) FullGreaM 2023, " + mitLicense + "</p></body></html>");
}

void Credits::autoscale () {
    this->ui->label->setGeometry(0, 0, this->width(), this->height());
}

Credits::~Credits()
{
    delete ui;
}
