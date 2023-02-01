#ifndef FREENET_SETTINGS_H
#define FREENET_SETTINGS_H

#include <QWidget>

namespace Ui {
class FreenetSettings;
}

class FreenetSettings : public QWidget
{
    Q_OBJECT

public:
    explicit FreenetSettings(QWidget *parent = nullptr);
    ~FreenetSettings();

private:
    Ui::FreenetSettings *ui;
};

#endif // FREENET_SETTINGS_H
