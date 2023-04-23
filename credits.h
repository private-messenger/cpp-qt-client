#ifndef CREDITS_H
#define CREDITS_H

#include <QWidget>

namespace Ui {
class Credits;
}

class Credits : public QWidget
{
    Q_OBJECT

public:
    explicit Credits(QWidget *parent = nullptr);
    ~Credits();
    void setupLocale (std::string locale);

protected slots:
    void autoscale ();

private:
    Ui::Credits *ui;
    QTimer *timer;
};

#endif // CREDITS_H
