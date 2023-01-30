#ifndef LOG_IN_FORM_H
#define LOG_IN_FORM_H

#include <QWidget>

namespace Ui {
class LogInForm;
}

class LogInForm : public QWidget
{
    Q_OBJECT

public:
    explicit LogInForm(QWidget *parent = nullptr);
    ~LogInForm();

private:
    Ui::LogInForm *ui;
};

#endif // LOG_IN_FORM_H
