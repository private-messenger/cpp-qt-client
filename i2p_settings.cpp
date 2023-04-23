#include "i2p_settings.h"
#include "qmessagebox.h"
#include "qtimer.h"
#include "ui_i2p_settings.h"
#include "locales.h"
#include "nodejs-run.h"
#include <QProcess>
#include <QApplication>
#include <iostream>

void I2pSettings::autoscale () {
    this->ui->tunnelsConfPath->setGeometry(0, 0, this->width(), 25);
    this->ui->binaryPath->setGeometry(0, 35, this->width(), 25);
    this->ui->i2pHttpPortLabel->setGeometry(0, 70, this->width(), 25);
    this->ui->httpProxy->setGeometry(0, 105, this->width(), 25);
    this->ui->save->setGeometry((this->width() / 2) - 50, 140, 100, 25);
    // Autoenable
    if (
        (this->i2pBin != this->ui->binaryPath->text()         ||
        this->i2pHttpPort != this->ui->httpProxy->value()     ||
        this->i2pConfig != this->ui->tunnelsConfPath->text()) && !this->ui->save->isEnabled()
    ) {
        this->ui->save->setEnabled(true);
    }
    else if (
        !(this->i2pBin != this->ui->binaryPath->text()        ||
        this->i2pHttpPort != this->ui->httpProxy->value()     ||
        this->i2pConfig != this->ui->tunnelsConfPath->text()) && this->ui->save->isEnabled()
    ) {
        this->ui->save->setEnabled(false);
    }
}

void I2pSettings::setupLocale (std::string locale) {
    Locales* loc = new Locales(locale);
    this->locale = locale;
    this->setWindowTitle(QString::fromStdString(loc->getLocaleVar("i2p.settings.title")));
    this->ui->tunnelsConfPath->setPlaceholderText(QString::fromStdString(loc->getLocaleVar("i2p.settings.tunnels_conf")));
    this->ui->binaryPath->setPlaceholderText(QString::fromStdString(loc->getLocaleVar("i2p.settings.bin_path")));
    this->ui->save->setText(QString::fromStdString(loc->getLocaleVar("i2p.settings.save_text")));
    this->ui->i2pHttpPortLabel->setText(QString::fromStdString(loc->getLocaleVar("i2p.settings.http_proxy_port")));
    //QString developedBy = "Разработчик: ";
}

int getIntPort (QString dataPort) {
    for (QString symbol : dataPort.split("")) {
        if (!(
            symbol.toStdString() == "0" ||
            symbol.toStdString() == "1" ||
            symbol.toStdString() == "2" ||
            symbol.toStdString() == "3" ||
            symbol.toStdString() == "4" ||
            symbol.toStdString() == "5" ||
            symbol.toStdString() == "6" ||
            symbol.toStdString() == "7" ||
            symbol.toStdString() == "8" ||
            symbol.toStdString() == "9" ||
            symbol.toStdString() == ""
        )) {
            return 5589;
        }
    }
    int parsedPort = dataPort.toInt();
    if (parsedPort <= 0 || parsedPort > 65535) {
        return 5589;
    }
    return parsedPort;
}

I2pSettings::I2pSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::I2pSettings)
{
    ui->setupUi(this);

    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(autoscale()));
    timer->start(1);  // И запустим таймер

    this->i2pBin      = nodejsRun("nodejs_tools/database/get-value.js i2pPathBinary");
    this->i2pHttpPort = getIntPort(nodejsRun("nodejs_tools/database/get-value.js i2pPortHttp"));
    this->i2pConfig   = nodejsRun("nodejs_tools/database/get-value.js i2pPathTunnels");

    this->ui->tunnelsConfPath->setText(
        this->i2pConfig
    );

    this->ui->binaryPath->setText(
        this->i2pBin
    );

    this->ui->httpProxy->setValue(this->i2pHttpPort);
}

I2pSettings::~I2pSettings()
{
    delete ui;
}

void I2pSettings::on_save_clicked()
{
    this->i2pBin    = this->ui->binaryPath->text();
    this->i2pConfig = this->ui->tunnelsConfPath->text();
    this->i2pHttpPort = this->ui->httpProxy->value();
    nodejsRun("nodejs_tools/database/set-value.js i2pPathBinary "  + this->i2pBin);
    nodejsRun("nodejs_tools/database/set-value.js i2pPathTunnels " + this->i2pConfig);
    nodejsRun("nodejs_tools/database/set-value.js i2pPortHttp " + QString(std::to_string(this->i2pHttpPort).c_str()));
    QMessageBox messageBox;
    Locales loc(this->locale);
    this->ui->save->setEnabled(false);
    messageBox.information(0, QString::fromStdString(loc.getLocaleVar("core.success")), QString::fromStdString(loc.getLocaleVar("i2p.settings.saved")));

    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    QCoreApplication::exit();
}

