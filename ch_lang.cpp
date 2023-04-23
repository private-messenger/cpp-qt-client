#include "ch_lang.h"
#include "ui_ch_lang.h"

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

void ChooseLanguageForm::setupLocale (std::string loc) {
    //
}

void ChooseLanguageForm::on_continueButton_clicked()
{
    this->choosed = true;
}
