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

private:
    Ui::GeneralSettings *ui;
};

#endif // GENERAL_SETTINGS_H
