#include "create-process.h"

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
