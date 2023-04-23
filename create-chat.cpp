#include "create-chat.h"
#include "qmessagebox.h"
#include "qtimer.h"
#include "ui_create-chat.h"
#include "create-process.h"
#include "nodejs-run.h"
#include "locales.h"

CreateChat::CreateChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateChat)
{
    ui->setupUi(this);

    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(autoscale()));
    timer->start(1);  // И запустим таймер
}

CreateChat::~CreateChat() {
    delete ui;
}

void CreateChat::autoscale () {
    this->ui->createChatButton->setGeometry(0, this->height() - 25, this->width(), 25);
    this->ui->creatingChatInfo->setGeometry(0, 0, this->width(), 40);
    this->ui->messageArea->setGeometry(0, 40, this->width(), this->height() - 65);
    // Auto access
    if (this->ui->messageArea->toPlainText() == "" && this->ui->createChatButton->isEnabled()) {
        this->ui->createChatButton->setEnabled(false);
    }
    else if (this->ui->messageArea->toPlainText() != "" && !this->ui->createChatButton->isEnabled()) {
        this->ui->createChatButton->setEnabled(true);
    }
}

void CreateChat::setupData (std::vector<QString> sendTo, std::string localeCode) {
    this->locale = localeCode;
    Locales locale(localeCode);
    this->sendTo = sendTo;
    this->setWindowTitle(QString::fromStdString(locale.getLocaleVar("create_chat.title")));
    this->ui->creatingChatInfo->setText("<html><head/><body><p><span style=\" font-weight:700;\">"+ QString::fromStdString(locale.getLocaleVar("create_chat.send_to")) +"</span>: "+ sendTo[0] +" <br/><span style=\" font-weight:700;\">"+ QString::fromStdString(locale.getLocaleVar("create_chat.message")) +"</span>:</p></body></html>");
    this->ui->createChatButton->setText(QString::fromStdString(locale.getLocaleVar("create_chat.send")));
}

void CreateChat::on_createChatButton_clicked() {
    Locales locale(this->locale);
    QString i2pPort   = nodejsRun("nodejs_tools/database/get-value.js i2pPortHttp");
    QString myAddress = nodejsRun("nodejs_tools/database/get-my-ip-address.js");
    //QString myAddress = "127.0.0.1:49862";
    //QString result = QString::fromStdString(curlStart("--proxy \"http://127.0.0.1:" + i2pPort + "\" -X POST \"http://" + myAddress + "/api/v1/messages.startDialog?to_id=" + sendTo[1] + "&message=" + this->ui->messageArea->toPlainText() + "\" -d \"{}\"").toStdString());
    QString result = QString::fromStdString(nodejsRun("nodejs_tools/requests/create-dialog.js " + sendTo[1] + " " + this->ui->messageArea->toPlainText()).toStdString());
    bool successfullSended = result == QString("ok");  // (!) После интеграции libcurl переписать
    QMessageBox messagebox;
    this->setEnabled(false);
    if (successfullSended) {
        messagebox.information(0, QString::fromStdString(locale.getLocaleVar("core.success")), QString::fromStdString(locale.getLocaleVar("create_chat.message_sended")));
        this->code = 1;
    }
    else {
        messagebox.critical(0, QString::fromStdString(locale.getLocaleVar("core.error")), QString::fromStdString(locale.getLocaleVar("create_chat.message_not_sended")) + result);
        this->code = -1;
    }
    this->ui->messageArea->setPlainText("");
    this->hide();
    this->setEnabled(true);
}
