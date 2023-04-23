#ifndef SENDMSGTHREAD_H
#define SENDMSGTHREAD_H

#include "nodejs-run.h"
#include <QThread>
#include "mainwindow.h"

class SendMsgThread : public QThread {
    Q_OBJECT
public:
    SendMsgThread (QString args, MainWindow* parent = nullptr) : QThread(parent) {
        this->args = args;
    }
signals:
    void finished();
protected:
    void run() override
    {
        // Выполняем функцию в потоке
        nodejsRun("nodejs_tools/requests/new-message.js " + args);

        // Завершаем поток и отправляем сигнал
        emit finished();
        deleteLater();
    }
private:
    QString args;
};

#endif // SENDMSGTHREAD_H
