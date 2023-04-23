#include "credits.h"
#include "ui_credits.h"
#include "locales.h"
#include <QTimer>

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
