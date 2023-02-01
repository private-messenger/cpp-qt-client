#ifndef I2P_SETTINGS_H
#define I2P_SETTINGS_H

#include <QWidget>

namespace Ui {
class I2pSettings;
}

class I2pSettings : public QWidget
{
    Q_OBJECT

public:
    explicit I2pSettings(QWidget *parent = nullptr);
    ~I2pSettings();

private:
    Ui::I2pSettings *ui;
};

#endif // I2P_SETTINGS_H
