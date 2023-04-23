#include "add-contact.h"
#include "nodejs-run.h"
#include "qmessagebox.h"
#include "qtimer.h"
#include "ui_add-contact.h"
#include "locales.h"

AddContact::AddContact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddContact)
{
    ui->setupUi(this);
    // Автомасштабирование и блокировка элементов
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(autoscale()));
    timer->start(1);
}

AddContact::~AddContact() {
    delete ui;
}

void AddContact::autoscale () {
    this->ui->tabs->setGeometry(0, 0, this->width(), this->height());

    this->ui->enterId->setGeometry(0, (this->ui->tabs->height() / 2) - 30, this->width(), 25);
    this->ui->addContactById->setGeometry((this->ui->tabs->width() / 2) - 55, (this->ui->tabs->height() / 2), 110, 25);

    this->ui->enterAddress->setGeometry(0, (this->ui->tabs->height() / 2) - 30, this->width(), 25);
    this->ui->addContactByAddress->setGeometry((this->ui->tabs->width() / 2) - 55, (this->ui->tabs->height() / 2), 110, 25);
}

void AddContact::setupLocale (std::string locale) {
    Locales loc(locale);
    this->setWindowTitle(QString::fromStdString(loc.getLocaleVar("add_contact.title")));
    this->ui->tabs->setTabText(0, QString::fromStdString(loc.getLocaleVar("add_contact.by_id")));
    this->ui->tabs->setTabText(1, QString::fromStdString(loc.getLocaleVar("add_contact.by_address")));

    this->ui->addContactById->setText(QString::fromStdString(loc.getLocaleVar("add_contact.add_contact")));
    this->ui->enterId->setPlaceholderText(QString::fromStdString(loc.getLocaleVar("add_contact.enter_id")));

    this->ui->addContactByAddress->setText(QString::fromStdString(loc.getLocaleVar("add_contact.add_contact")));
    this->ui->enterAddress->setPlaceholderText(QString::fromStdString(loc.getLocaleVar("add_contact.enter_address")));

    this->locale = locale;
}

void AddContact::on_addContactById_clicked() {
    // Пожалуй это побудет пока в разработке до лучших времён
}


void AddContact::on_addContactByAddress_clicked() {
    QString result = nodejsRun("nodejs_tools/requests/add-contact-by-address.js " + this->ui->enterAddress->text());
    QMessageBox messagebox;
    Locales loc(this->locale);
    if (result != QString("ok")) {
        messagebox.critical(0, QString::fromStdString(loc.getLocaleVar("core.error")), QString::fromStdString(loc.getLocaleVar("add_contact.conact_add_error")));
    }
    else {
        messagebox.information(0, QString::fromStdString(loc.getLocaleVar("core.success")), QString::fromStdString(loc.getLocaleVar("add_contact.conact_added")));
        this->updated = true;
    }
    this->ui->enterAddress->setText("");
    this->hide();
}
