#include "freenet_settings.h"
#include "qtimer.h"
#include "locales.h"
#include "ui_freenet_settings.h"

void FreenetSettings::autoscale () {
    this->ui->freenetInDev->setGeometry(0, 0, this->width(), this->height());
}

void FreenetSettings::setupLocale (std::string locale) {
    Locales* loc = new Locales(locale);
    this->setWindowTitle(QString::fromStdString(loc->getLocaleVar("freenet.settings.title")));
    //QString developedBy = "Разработчик: ";
    this->ui->freenetInDev->setText(QString::fromStdString("<html><head/><body><p align=\"center\"><span style=\" font-size:36pt; font-weight:700; color:#8a8a8a;\">" + loc->getLocaleVar("labels.mainw.indev") + "</span></p></body></html>"));
}


FreenetSettings::FreenetSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FreenetSettings)
{
    ui->setupUi(this);

    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(autoscale()));
    timer->start(1);  // И запустим таймер
}

FreenetSettings::~FreenetSettings()
{
    delete ui;
}
