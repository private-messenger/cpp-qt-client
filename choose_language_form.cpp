#include "choose_language_form.h"
#include "ui_choose_language_form.h"

ChooseLanguageForm::ChooseLanguageForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseLanguageForm)
{
    ui->setupUi(this);
}

ChooseLanguageForm::~ChooseLanguageForm()
{
    delete ui;
}
