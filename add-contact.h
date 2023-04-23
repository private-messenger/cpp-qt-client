#ifndef ADDCONTACT_H
#define ADDCONTACT_H

#include <QWidget>

namespace Ui {
class AddContact;
}

class AddContact : public QWidget
{
    Q_OBJECT

public:
    explicit AddContact(QWidget *parent = nullptr);
    ~AddContact();
    void setupLocale (std::string locale);
    bool updated = false;

private:
    Ui::AddContact *ui;
    QTimer* timer;
    std::string locale = "ru_RU";

private slots:
    void autoscale                      ();

    void on_addContactById_clicked      ();
    void on_addContactByAddress_clicked ();
};

#endif // ADDCONTACT_H
