#ifndef CREATE_PROCESS_H
#define CREATE_PROCESS_H

#include <QProcess>
#include <QStringList>

unsigned char* startProcess (char* command, QStringList args={});

#endif // CREATE_PROCESS_H
