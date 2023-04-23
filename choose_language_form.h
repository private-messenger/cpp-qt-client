#ifndef CHOOSE_LANGUAGE_FORM_H
#define CHOOSE_LANGUAGE_FORM_H

#include <QWidget>

namespace Ui {
class ChooseLanguageForm;
}

class ChooseLanguageForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseLanguageForm(QWidget *parent = nullptr);
    ~ChooseLanguageForm();

private:
    Ui::ChooseLanguageForm *ui;
};

#endif // CHOOSE_LANGUAGE_FORM_H
