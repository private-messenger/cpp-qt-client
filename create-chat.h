#ifndef CREATECHAT_H
#define CREATECHAT_H

#include <QWidget>

namespace Ui {
class CreateChat;
}

class CreateChat : public QWidget
{
    Q_OBJECT

public:
    explicit CreateChat(QWidget *parent = nullptr);
    ~CreateChat();
    std::vector<QString> sendTo;
    void setupData (std::vector<QString> sendTo, std::string localeCode);
    QTimer* timer;
    int code = 0;

private slots:
    void autoscale ();
    void on_createChatButton_clicked();

private:
    Ui::CreateChat *ui;
    std::string locale;
};

#endif // CREATECHAT_H
