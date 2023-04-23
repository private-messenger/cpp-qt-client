#include "key-viewer.h"
#include "qtimer.h"
#include "ui_key-viewer.h"
#include "locales.h"

KeyViewer::KeyViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KeyViewer)
{
    ui->setupUi(this);

    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(autoscale()));
    timer->start(1);  // И запустим таймер
}

KeyViewer::~KeyViewer()
{
    delete ui;
}

void KeyViewer::autoscale () {
    //this->ui->freenetInDev->setGeometry(0, 0, this->width(), this->height());
    this->ui->textBrowser->setGeometry(0, 0, this->width(), this->height());
}

void KeyViewer::setupLocale (std::string locale) {
    Locales* loc = new Locales(locale);
    this->locale = locale;
    this->setWindowTitle(QString::fromStdString(loc->getLocaleVar("kv.title")));
    /*this->ui->tunnelsConfPath->setPlaceholderText(QString::fromStdString(loc->getLocaleVar("i2p.settings.tunnels_conf")));
    this->ui->binaryPath->setPlaceholderText(QString::fromStdString(loc->getLocaleVar("i2p.settings.bin_path")));
    this->ui->save->setText(QString::fromStdString(loc->getLocaleVar("i2p.settings.save_text")));*/
    //QString developedBy = "Разработчик: ";
}

void KeyViewer::setData (vector<QString> data) {
    Locales loc(this->locale);
    QString keyType = data.at(2) == "0" ? "kv.type.key" : data.at(2) == "1" ? "kv.type.public" : "kv.type.private";
    this->ui->textBrowser->setText(QString("<strong>") + QString(loc.getLocaleVar("kv.name").data()) + QString("</strong>: ") + data.at(0) + QString("<br/>\n<strong>") +
                                   QString(loc.getLocaleVar("kv.alg").data()) + QString("</strong>: ") + data.at(1) + QString("<br/>\n<strong>") +
                                   QString(loc.getLocaleVar("kv.type").data()) + QString("</strong>: ") + QString(loc.getLocaleVar(keyType.toStdString()).data()) +
                                   QString("<br/>\n<strong>") + QString(loc.getLocaleVar("kv.coding").data()) +  QString("</strong>: ") + data.at(3) + QString("<br/>\n<center><strong>") +
                                   QString(loc.getLocaleVar("kv.data").data()) + QString("</strong></center><hr>") + data.at(4) + QString("<hr>"));
}
