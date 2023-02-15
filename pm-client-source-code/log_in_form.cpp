#include "log_in_form.h"
#include "ui_log_in_form.h"
#include "mainwindow.h"
#include "locales.h"
#include <QTimer>
#include <QMessageBox>
#include "databaseAI.h"

/*
Уважаемые (и не очень) любители комментариев "на английском языке",
а также уважаемые (и, опять же, не очень) любители #ихборьбы с ненависьтью
обычного русскоговорящего населения (да и русских в частности на каком
языке они бы не общались), которые родились с Российским (или Белорусским
гражданством). Этот код написан гражданином Российской Федерации: русским и на
половину украинцем. Если вам не нравится этот факт, или факт того, что тут
пишут комментарии на русском языке - ищите другие проекты. Если вам нужны
мои комментарии пользуйтесь либо словарём, либо гугл (или яндекс) переводчиком

Приходько Н.С. (FullGreaM) 2023 год
-------------------------------------------------------------------------------
Dear (and not so) fans of comments "in English",
as well as dear (and, again, not so) fans of #cancelculture the non-writing of the
ordinary Russian-speaking population (and Russians in particular in what language
they would not communicate in the language), who were born with Russian (or Belarusian
citizenship). This code is written by a citizen of the Russian Federation: Russian and
half Ukrainian. If you don't like this fact, or the fact that comments are written here
in Russian - look for other projects. If you need my comments either use a dictionary
or Google (or Bing) translator

Prikhodko N.S. (FullGreaM) 2023
*/

LogInForm::LogInForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogInForm)
{
    ui->setupUi(this);
    // Автомасштабирование и блокировка элементов
    this->timerScale = new QTimer(this);
    connect(timerScale, SIGNAL(timeout()), this, SLOT(autoscale()));
    timerScale->start(1);
}

void LogInForm::setupDatabase (DatabaseAppInterface* database) {
    this->database = database;
}

void LogInForm::on_signUpButton_clicked () {
    Locales* loc = new Locales(locale);
    if (this->ui->passwordField_up->text() != this->ui->repeatPasswordField_up->text()) {
        QMessageBox messageBox;
        messageBox.critical(0, QString::fromStdString(loc->getLocaleVar("auth.error")), QString::fromStdString(loc->getLocaleVar("auth.nomatch_passwords")));
    }
    else {  // Всё ок
        if(this->database->reg(
            this->ui->loginField_up->text().toStdString(),
            this->ui->passwordField_up->text().toStdString()
        )) {
            QMessageBox messageBox;
            messageBox.information(0, QString::fromStdString(loc->getLocaleVar("auth.successful.title")), QString::fromStdString(loc->getLocaleVar("auth.successful")));
        }
    }
}

void LogInForm::setupLocale (std::string locale) {
    Locales* loc = new Locales(locale);
    this->locale = locale;
    this->setWindowTitle(QString::fromStdString(loc->getLocaleVar("auth.title")));
    // Общие переменные
    QString login = QString::fromStdString(loc->getLocaleVar("auth.login"));
    QString password = QString::fromStdString(loc->getLocaleVar("auth.password"));
    QString repeatPassword = QString::fromStdString(loc->getLocaleVar("auth.repeat_password"));
    // Табы
    this->ui->tabWidget->setTabText(0, QString::fromStdString(loc->getLocaleVar("auth.tab.sign_in")));
    this->ui->tabWidget->setTabText(1, QString::fromStdString(loc->getLocaleVar("auth.tab.sign_up")));
    // Вход
    this->ui->label_login->setText("<html><head/><body><p align=\"center\">" + login + "</p></body></html>");
    this->ui->label_password->setText("<html><head/><body><p align=\"center\">" + password + "</p></body></html>");
    this->ui->signInButton->setText(QString::fromStdString(loc->getLocaleVar("auth.sign_in.button")));
    this->ui->signInFromFileButton->setText(QString::fromStdString(loc->getLocaleVar("auth.sign_in_file.button")));
    // Регистрация
    this->ui->label_login_up->setText("<html><head/><body><p align=\"center\">" + login + "</p></body></html>");
    this->ui->label_password_up->setText("<html><head/><body><p align=\"center\">" + password + "</p></body></html>");
    this->ui->label_password_up_2->setText("<html><head/><body><p align=\"center\">" + repeatPassword + "</p></body></html>");
    this->ui->signUpButton->setText(QString::fromStdString(loc->getLocaleVar("auth.sign_up.button")));
}

void LogInForm::autoscale () {
    this->ui->tabWidget->setGeometry(0, 0, this->width(), this->height());
    // Вход
    this->ui->label_login->setGeometry(0, 0, this->width(), 30);
    this->ui->loginField->setGeometry(0, 30, this->width(), 24);

    this->ui->label_password->setGeometry(0, 60, this->width(), 30);
    this->ui->passwordField->setGeometry(0, 90, this->width(), 24);

    this->ui->signInButton->setGeometry((this->width() / 2) - 40, 130, 80, 24);
    this->ui->signInFromFileButton->setGeometry((this->width() / 2) - 50, 170, 100, 24);
    // Авторизация
    this->ui->label_login_up->setGeometry(0, 0, this->width(), 30);
    this->ui->loginField_up->setGeometry(0, 30, this->width(), 24);

    this->ui->label_password_up->setGeometry(0, 60, this->width(), 30);
    this->ui->passwordField_up->setGeometry(0, 90, this->width(), 24);

    this->ui->label_password_up_2->setGeometry(0, 120, this->width(), 30);
    this->ui->repeatPasswordField_up->setGeometry(0, 150, this->width(), 24);

    this->ui->signUpButton->setGeometry((this->width() / 2) - 75, 190, 150, 24);

    // Блокировка
    if (
        (this->ui->loginField_up->text() == "" || this->ui->passwordField_up->text() == "" || (this->ui->passwordField_up->text() != this->ui->repeatPasswordField_up->text())) &&
        this->ui->signUpButton->isEnabled()
    ) {
        this->ui->signUpButton->setEnabled(false);
    }
    else if (
        !(this->ui->loginField_up->text() == "" || this->ui->passwordField_up->text() == "" || (this->ui->passwordField_up->text() != this->ui->repeatPasswordField_up->text())) &&
        !this->ui->signUpButton->isEnabled()
    ) {
        this->ui->signUpButton->setEnabled(true);
    }
}

LogInForm::~LogInForm() {
    delete ui;
}
