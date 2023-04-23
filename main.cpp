#include "mainwindow.h"
#include <QApplication>
#include <vector>

#include "nodejs-run.h"

/*
 * Для линукса необходимо: sudo apt-get install libsqlite3-dev nodejs
 */

//#include <iostream>

std::string getActiveLocale () {
    return std::string(nodejsRun("nodejs_tools/database/get-value.js activeLang"));
}

int main (int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    if (!w.error) {
        bool isAuthed = w.isAuthed();
        std::string activeLocale = getActiveLocale();
        bool localeSetuped = activeLocale != "";
        if (localeSetuped) {
            w.setupLocale(activeLocale);
        }
        else {
            w.chooseLocale();
        }
        w.show();
        if (!isAuthed) {
            w.setDisabled(true);
            w.showLogIn();
        }
        else {
            w.startServer();
        }
        return a.exec();
    }
    else {
        return -1;
    }
}
