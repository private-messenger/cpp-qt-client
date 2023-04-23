#include "log_in_form.h"
#include "ui_log_in_form.h"
#include "mainwindow.h"
#include "locales.h"
#include <QTimer>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include "databaseAI.h"

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
        if (this->database->reg(
            this->ui->loginField_up->text().toStdString(),
            this->ui->passwordField_up->text().toStdString()
        )) {
            QMessageBox messageBox;
            this->isSuccess = true;
            messageBox.information(0,
                QString::fromStdString(loc->getLocaleVar("auth.successful.title")),
                QString::fromStdString(loc->getLocaleVar("auth.successful.label"))
            );
            this->hide();
        }
        else {

        }
    }

    delete loc;
}

void LogInForm::on_signInButton_clicked()
{
    Locales* loc = new Locales(locale);
    delete loc;
    std::string login = (this->ui->loginField->text()).toStdString();
    std::string password = (this->ui->passwordField->text()).toStdString();

    if (this->database->auth(login, password)) {
        QMessageBox messageBox;
        this->isSuccess = true;
        messageBox.information(0,
            QString::fromStdString(loc->getLocaleVar("auth.successful.title")),
            QString::fromStdString(loc->getLocaleVar("auth.successful.label"))
        );
        this->hide();
    }
    else {
        QMessageBox errorBox;
        errorBox.critical(0,
            QString::fromStdString(loc->getLocaleVar("auth.error")),
            QString::fromStdString(loc->getLocaleVar("auth.wrong_password"))
        );
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

    delete loc;
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

void LogInForm::on_signInFromFileButton_clicked() {
    Locales loc(this->locale);
    QString filename = QFileDialog::getOpenFileName(this, QString::fromStdString(loc.getLocaleVar("core.open_file")), QDir::homePath(), QString::fromStdString(loc.getLocaleVar("core.open_file.extensions")));
    if (!filename.isEmpty()) {
        // Открываем файл по выбранному пути
        bool isSuccess = nodejsRun("nodejs_tools/database/log-in-from-file.js " + filename) == QString("ok");
        if (isSuccess) {
            QMessageBox messageBox;
            this->isSuccess = true;
            messageBox.information(0,
                QString::fromStdString(loc.getLocaleVar("auth.successful.title")),
                QString::fromStdString(loc.getLocaleVar("auth.successful.label"))
            );
            this->hide();
        }
        else {
            QMessageBox errorBox;
            errorBox.critical(0,
                QString::fromStdString(loc.getLocaleVar("auth.error")),
                QString::fromStdString(loc.getLocaleVar("auth.wrong_password"))
            );
        }
    }
}

