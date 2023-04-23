#include "choose_language.h"
#include "ui_choose_language.h"

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

void ChooseLanguageForm::on_continueButton_clicked()
{
    this->hide();
}

