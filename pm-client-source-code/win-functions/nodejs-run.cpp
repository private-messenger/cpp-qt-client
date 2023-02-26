#include "nodejs-run.h";

QByteArray nodejsRun (QString pathToFile) {
    char* command = "nodejs/node";
    unsigned char* result = startProcess(command, pathToFile.split(" "));
    return QByteArray((char*)result);
}
