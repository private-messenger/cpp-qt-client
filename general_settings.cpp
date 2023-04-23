#include "general_settings.h"
#include "ui_general_settings.h"
#include "locales.h"

#include <QTimer>

GeneralSettings::GeneralSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralSettings)
{
    ui->setupUi(this);

    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(autoscale()));
    timer->start(1);  // И запустим таймер
}

GeneralSettings::~GeneralSettings() {
    delete ui;
}

void GeneralSettings::setupLocale (std::string locale) {
    Locales loc(locale);
    this->setWindowTitle(QString::fromStdString(loc.getLocaleVar("general_settings.title")));
    this->ui->maxAdrBookLabel->setText(QString::fromStdString(loc.getLocaleVar("general_settings.max_adr_book.label")));
    this->ui->maxAccountLabel->setText(QString::fromStdString(loc.getLocaleVar("general_settings.max_accounts.label")));
    this->ui->serversLabel->setText(QString("<center>") + QString::fromStdString(loc.getLocaleVar("general_settings.servers.label")) + QString("</center>"));
    this->ui->editHost->setText(QString::fromStdString(loc.getLocaleVar("general_settings.edit_host")));
    this->ui->applySettings->setText(QString::fromStdString(loc.getLocaleVar("general_settings.apply_settings_button")));
    this->ui->enableDebugMode->setText(QString::fromStdString(loc.getLocaleVar("general_settings.debug_mode")));
}

void GeneralSettings::autoscale () {
    this->ui->maxAdrBookLabel->setGeometry(5, 5, this->width() - 10, 25);
    this->ui->maxAdrBook->setGeometry(5, 35, this->width() - 10, 25);
    this->ui->maxAccountLabel->setGeometry(5, 65, this->width() - 10, 25);
    this->ui->maxAccount->setGeometry(5, 95, this->width() - 10, 25);
    this->ui->serversLabel->setGeometry(5, 125, this->width() - 10, 25);
    this->ui->hostsList->setGeometry(5, 155, this->width() - 10, this->height() - 230);
    this->ui->addHost->setGeometry(5, this->ui->hostsList->height() + 155, 30, 25);
    this->ui->rmHost->setGeometry(35, this->ui->hostsList->height() + 155, 30, 25);
    this->ui->editHost->setGeometry(65, this->ui->hostsList->height() + 155, this->width() - 70, 25);
    this->ui->applySettings->setGeometry(5, this->ui->editHost->y() + 25, this->width() - 10, 25);

    this->ui->enableDebugMode->setGeometry(5, this->height() - 25, this->width() - 5, 25);

    /*Autoaccess*/
    if (this->ui->hostsList->currentRow() != -1 && !this->ui->addHost->isEnabled() && !this->ui->rmHost->isEnabled() && !this->ui->editHost->isEnabled()) {
        this->ui->editHost->setEnabled(true);
        this->ui->addHost->setEnabled(true);
        this->ui->rmHost->setEnabled(true);
    }
    else if (this->ui->hostsList->currentRow() == -1 && this->ui->addHost->isEnabled() && this->ui->rmHost->isEnabled() && this->ui->editHost->isEnabled()) {
        this->ui->editHost->setEnabled(false);
        this->ui->addHost->setEnabled(false);
        this->ui->rmHost->setEnabled(false);
    }
}
