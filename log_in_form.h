#ifndef LOG_IN_FORM_H
#define LOG_IN_FORM_H

#include <QWidget>
#include "databaseAI.h"

namespace Ui {
class LogInForm;
}

class LogInForm : public QWidget
{
    Q_OBJECT

public:
    explicit LogInForm(QWidget *parent = nullptr);
    ~LogInForm();
    void setupLocale (std::string locale);
    void setupDatabase (DatabaseAppInterface* database);
    DatabaseAppInterface* database = 0;
    std::string locale;
    bool isSuccess = false;
protected slots:
    void autoscale ();
private slots:
    void on_signInButton_clicked ();
    void on_signUpButton_clicked ();
    void on_signInFromFileButton_clicked();

private:
    Ui::LogInForm *ui;
    QTimer *timerScale;
};

#endif // LOG_IN_FORM_H
