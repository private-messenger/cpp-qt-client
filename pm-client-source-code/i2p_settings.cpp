#include "i2p_settings.h"
#include "ui_i2p_settings.h"

I2pSettings::I2pSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::I2pSettings)
{
    ui->setupUi(this);
}

I2pSettings::~I2pSettings()
{
    delete ui;
}
