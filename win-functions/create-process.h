#ifndef CREATE_PROCESS_H
#define CREATE_PROCESS_H

#include <QProcess>
#include <QStringList>

unsigned char* startProcess (char* command, QStringList args={});
QByteArray curlStart (QString pathToFile);

class StartProcess {
public:
    StartProcess (QObject* qObject);
    void run     ();
    void restart ();
    ~StartProcess ();
private:
    QProcess msgServer;
    QProcess i2pServer;
};

#endif // CREATE_PROCESS_H
