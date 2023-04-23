#ifndef GENERAL_SETTINGS_H
#define GENERAL_SETTINGS_H

#include <QWidget>

namespace Ui {
class GeneralSettings;
}

class GeneralSettings : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralSettings(QWidget *parent = nullptr);
    ~GeneralSettings();
    void setupLocale (std::string locale);

private:
    Ui::GeneralSettings *ui;
    QTimer* timer;

private slots:
    void autoscale ();
};

#endif // GENERAL_SETTINGS_H
