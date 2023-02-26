#include "databaseAI.h"
#include "sqlite3.h"
#include <fstream>
#include "cryptography.h"

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

#include <iostream>
#include "nodejs-run.h"

DatabaseAppInterface::DatabaseAppInterface() {
    std::ifstream file ("appdata");
    if (!file.is_open()) {
        this->raisedError = true;
        this->dbError = "sql.errCreate";
        this->details = "File 'appdata' not founded";
    }
    else {
        file.close();
        std::string dbCheckResult = nodejsRun("nodejs_tools/database/here.js").data();
        if (dbCheckResult != std::string("ok")) {
            this->raisedError = true;
            this->dbError = "sql.errCreate";
            this->details = dbCheckResult == "SQLEasy error: this table not founded." ? (char*)"SQLEasy error: this table not founded." : (char*)"Unknown error";
        }
    }
}

void DatabaseAppInterface::setValue (char* key, char* value) {
    nodejsRun("nodejs_tools/database/set-value.js " + QString(key) + " " + QString(value));
}

bool DatabaseAppInterface::hasAccount (char* id) {
    std::string dbCheckResult = nodejsRun("nodejs_tools/database/has-account.js " + QString(id)).data();
    return dbCheckResult == std::string("1");
}

bool DatabaseAppInterface::reg (std::string login, std::string password) {
    std::string dbCheckResult = nodejsRun("nodejs_tools/database/register.js " + QString(login.c_str()) + " " + QString(password.c_str())).data();
    bool result = dbCheckResult == std::string("ok");
    if (!result) {
        this->raisedError = true;
        this->dbError = "sql.errCreate";
        this->details = "no details";
        return false;
    }
    return true;
}

bool DatabaseAppInterface::getAuthed () {
    std::string dbCheckResult = nodejsRun("nodejs_tools/database/authed.js").data();
    return dbCheckResult == std::string("1");
}

DatabaseAppInterface::~DatabaseAppInterface () {
    //sqlite3_close(database);
    //delete database;
}
