#ifndef CREATE_PROCESS_H
#define CREATE_PROCESS_H

#include <QProcess>
#include <QStringList>

unsigned char* startProcess (char* command, QStringList args={});

class StartProcess {
public:
    StartProcess (QObject* qObject);
    void run ();
    ~StartProcess ();
private:
    QProcess process;
};

#endif // CREATE_PROCESS_H
