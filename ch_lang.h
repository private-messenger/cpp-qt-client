#ifndef CH_LANG_H
#define CH_LANG_H

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
    bool choosed = false;
    std::string choosenLanguage = "";
    void setupLocale (std::string loc);

private slots:
    void on_continueButton_clicked();

private:
    Ui::ChooseLanguageForm *ui;
};

#endif // CH_LANG_H
