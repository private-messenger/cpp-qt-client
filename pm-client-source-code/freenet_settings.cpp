#include "freenet_settings.h"
#include "ui_freenet_settings.h"

FreenetSettings::FreenetSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FreenetSettings)
{
    ui->setupUi(this);
}

FreenetSettings::~FreenetSettings()
{
    delete ui;
}
