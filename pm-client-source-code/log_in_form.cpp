#include "log_in_form.h"
#include "ui_log_in_form.h"

LogInForm::LogInForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogInForm)
{
    ui->setupUi(this);
}

LogInForm::~LogInForm()
{
    delete ui;
}
