#include "mainwindow.h"
#include <QApplication>

#include "nodejs-run.h"

/*
Уважаемые (и не очень) любители комментариев "на английском языке",
а также уважаемые (и, опять же, не очень) любители #ихборьбы с ненависьтью
обычного русскоговорящего населения (да и русских в частности на каком
языке они бы не общались), которые родились с Российским (или Белорусским
гражданством). Этот код написан гражданином Российской Федерации: русским и на
половину украинцем. Если вам не нравится этот факт, или факт того, что тут
пишут комментарии на русском языке - ищите другие проекты. Если вам нужны
мои комментарии пользуйтесь либо словарём, либо гугл (или яндекс) переводчиком

Приходько Н.С. (FullGreaM) 2023 год
-------------------------------------------------------------------------------
Dear (and not so) fans of comments "in English",
as well as dear (and, again, not so) fans of #cancelculture the non-writing of the
ordinary Russian-speaking population (and Russians in particular in what language
they would not communicate in the language), who were born with Russian (or Belarusian
citizenship). This code is written by a citizen of the Russian Federation: Russian and
half Ukrainian. If you don't like this fact, or the fact that comments are written here
in Russian - look for other projects. If you need my comments either use a dictionary
or Google (or Bing) translator

Prikhodko N.S. (FullGreaM) 2023
*/

/*
 * Для линукса необходимо: sudo apt-get install libsqlite3-dev nodejs
*/

//#include <iostream>

int main (int argc, char *argv[]) {
    /*char* ok = (char*)nodejsRun("nodejs_tools/cryptography/md5-gen.js");
    qDebug(ok);*/

    QApplication a(argc, argv);
    MainWindow w;
    if (!w.error) {
        bool isAuthed = w.isAuthed();
        w.show();
        std::string activeLocale = "ru_RU";
        w.setupLocale(activeLocale);
        if (!isAuthed) {
            w.setDisabled(true);
            w.showLogIn();
        }
        return a.exec();
    }
    else {
        return -1;
    }
}
