#ifndef CHOOSE_LANGUAGE_H
#define CHOOSE_LANGUAGE_H

#include <QWidget>
#include <string>

namespace Ui {
class ChooseLanguageForm;
}

class ChooseLanguageForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseLanguageForm(QWidget *parent = nullptr);
    ~ChooseLanguageForm();
    std::string choosenLanguage = "ru_RU";
    std::string localesList[3] = { "ru_RU", "en_UK", "ua_UA" };
    bool choosed = false;
    void setupLocale ();

private slots:
    void autoselect ();
    void autoscale ();

    void on_continueButton_clicked ();

private:
    Ui::ChooseLanguageForm *ui;
};

#endif // CHOOSE_LANGUAGE_H
