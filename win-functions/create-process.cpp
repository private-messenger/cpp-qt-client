#include "create-process.h"
#include "qwidget.h"
#include "nodejs-run.h"
#include <QDir>

StartProcess::StartProcess (QObject* qObject) : msgServer(qObject), i2pServer(qObject) {
    //
}

StartProcess::~StartProcess() {
    //
}

void StartProcess::run () {
    this->msgServer.start("nodejs/node", { "nodejs_tools/server/server.js" });
    // Получим путь до i2p-бинарника
    QString i2pPathBinary = QString(nodejsRun("nodejs_tools/database/get-value.js i2pPathBinary").data());
    QString i2pPathTunnels = QString(nodejsRun("nodejs_tools/database/get-value.js i2pPathTunnels").data());
    QString i2pHttpProxyPort = QString(nodejsRun("nodejs_tools/database/get-value.js i2pPortHttp").data());
    nodejsRun("nodejs_tools/i2p/setup-config.js");
    this->i2pServer.start(i2pPathBinary, { QString("--tunconf=") + i2pPathTunnels, QString("--httpproxy.port=") + i2pHttpProxyPort, QString("--datadir=") + QDir::currentPath(), QString("--floodfill") });
    /*qDebug(" >> ");
    qDebug(i2pPathBinary.toStdString().c_str());
    qDebug(i2pPathTunnels.toStdString().c_str());
    qDebug(" << ");*/
}

void StartProcess::restart () {
    this->msgServer.kill();
    this->i2pServer.kill();
    this->run();
}

unsigned char* startProcess (char* command, QStringList args) {
   QString program = command;
   QProcess process(new QObject);
   process.start(command, args);
   process.waitForReadyRead();
   //qDebug(process.readAll());
   process.waitForFinished();
   return (unsigned char*)process.readAll().constData();
}

QByteArray curlStart (QString pathToFile) {
    char* command = "curl/curl";
    //pathToFile = pathToFile + QString(" --data-ascii @- -qs");
    pathToFile = QString("") + pathToFile;
    unsigned char* result = startProcess(command, pathToFile.split(" "));
    return QByteArray((char*)result);
}
