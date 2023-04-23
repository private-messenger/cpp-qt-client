#include "databaseAI.h"
#include "sqlite3.h"
#include <fstream>
#include<QDir>
#include "cryptography.h"

#include <iostream>
#include "nodejs-run.h"

DatabaseAppInterface::DatabaseAppInterface() {
    //std::ifstream file ("appdata");
    std::ifstream file ("appdata");
    if (!file.is_open()) {
    //if (false) {
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
            qDebug(dbCheckResult.c_str());
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

bool DatabaseAppInterface::auth (std::string login, std::string password) {
    std::string dbCheckResult = nodejsRun("nodejs_tools/database/log-in.js " + QString(login.c_str()) + " " + QString(password.c_str())).data();
    return dbCheckResult == std::string("ok");
}

bool DatabaseAppInterface::getAuthed () {
    std::string dbCheckResult = nodejsRun("nodejs_tools/database/authed.js").data();
    return dbCheckResult == std::string("1");
}

DatabaseAppInterface::~DatabaseAppInterface () {
    //sqlite3_close(database);
    //delete database;
}
