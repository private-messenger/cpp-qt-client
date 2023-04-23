#include "create-process.h"
#include "qwidget.h"

StartProcess::StartProcess (QObject* qObject) : process(qObject) {
    //QProcess process(qObject);
}

StartProcess::~StartProcess() {
    //delete process;
}

void StartProcess::run () {
    this->process.start("node", { "nodejs_tools/server/server.js" });
}

unsigned char* startProcess (char* command, QStringList args) {
   QString program = command;
   QProcess process(new QObject);
   //process->setProcessChannelMode(QProcess::MergedChannels);
   //process->setReadChannel (QProcess::StandardError);
   //process.start(QProcess::tr(command));
   process.start(command, args);
   process.waitForReadyRead();
   //qDebug(process.readAll());
   process.waitForFinished();
   return (unsigned char*)process.readAll().constData();
}
