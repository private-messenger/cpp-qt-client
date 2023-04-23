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
    void setupLocale (std::string locale);

private:
    Ui::I2pSettings *ui;
    QTimer*         timer;
    QString         i2pBin;
    QString         i2pConfig;
    int             i2pHttpPort = 5589;
    std::string     locale;

private slots:
    void autoscale ();
    void on_save_clicked();
};

#endif // I2P_SETTINGS_H
