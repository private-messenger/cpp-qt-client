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

DatabaseAppInterface::DatabaseAppInterface() {
    std::ifstream file ("appdata");
    if (!file.is_open()) {
        this->raisedError = true;
        this->dbError = "sql.errCreate";
        this->details = "File 'appdata' not founded";
    }
    else {
        file.close();
        if (sqlite3_open("appdata", &database)) {
            this->raisedError = true;
            this->dbError = "sql.errCreate";
            this->details = (char*)sqlite3_errmsg(database);
        }
    }
}

char* generateId () {
    return "tempID";
}

bool DatabaseAppInterface::reg (std::string login, std::string password) {
    char* id = generateId();
    char* i2pKey = "";  // (!) Сделать нормальную генерацию i2p ключа
    std::string sql("INSERT INTO users(id, login, password, public_key, privkey_encoded, i2pkey_encoded, storagekey_encoded)"
                    " VALUES (?, ?, ?, ?, ?, ?, ?);");
    sqlite3_stmt *stmt = NULL;
    int rc = sqlite3_prepare(database, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        this->raisedError = true;
        this->dbError = "sql.errCreate";
        this->details = (char*)sqlite3_errmsg(database);
    }
    else {
        // Биндим id пользователя
        rc = sqlite3_bind_blob(stmt, 1, id, sizeof(id), SQLITE_STATIC);
        // Биндим логин пользователя
        rc = rc == SQLITE_OK ? sqlite3_bind_blob(stmt, 1, login.c_str(), sizeof(login.c_str()), SQLITE_STATIC) : rc;
        // Инициализация шифрования по AES256 и RSA
        unsigned char* logPasKey = (unsigned char*)(login + ":" + password).c_str();
        AES256* encoding = new AES256((unsigned char*)(logPasKey));
        AES256* storage = new AES256((unsigned char*)(generateId()));
        RSA* rsaKeys = new RSA(NULL, NULL);
        // Шифруем ключи, пароль
        char* passwordEncoded = (char*)encoding->encode(logPasKey);
        char* publicKey = (char*)rsaKeys->publickey;
        char* privkeyEncoded = (char*)encoding->encode((unsigned char*)(rsaKeys->privatekey));
        char* i2pKeyEncoded = (char*)encoding->encode((unsigned char*)(i2pKey));
        char* storageKeyEncoded = (char*)encoding->encode((unsigned char*)(storage->privatekey));
        // Биндим пароль и ключи в зашифрованном виде
        rc = rc == SQLITE_OK ? sqlite3_bind_blob(stmt, 1, passwordEncoded, sizeof(passwordEncoded), SQLITE_STATIC) : rc;
        rc = rc == SQLITE_OK ? sqlite3_bind_blob(stmt, 1, publicKey, sizeof(publicKey), SQLITE_STATIC) : rc;
        rc = rc == SQLITE_OK ? sqlite3_bind_blob(stmt, 1, privkeyEncoded, sizeof(privkeyEncoded), SQLITE_STATIC) : rc;
        rc = rc == SQLITE_OK ? sqlite3_bind_blob(stmt, 1, i2pKeyEncoded, sizeof(i2pKeyEncoded), SQLITE_STATIC) : rc;
        rc = rc == SQLITE_OK ? sqlite3_bind_blob(stmt, 1, storageKeyEncoded, sizeof(storageKeyEncoded), SQLITE_STATIC) : rc;

        if (rc != SQLITE_OK) {
            this->raisedError = true;
            this->dbError = "sql.errCreate";
            this->details = (char*)sqlite3_errmsg(database);

            return false;
        }
        else {
            rc = sqlite3_step(stmt);
            if (rc != SQLITE_OK) {
                this->raisedError = true;
                this->dbError = "sql.errCreate";
                this->details = (char*)sqlite3_errmsg(database);

                return false;
            }
            else return true;
        }
    }
}

bool DatabaseAppInterface::getAuthed () {
    // return false;
    std::string sql("SELECT value FROM envs WHERE key='authedAccount';");
    sqlite3_stmt *stmt = NULL;
    int rc = sqlite3_prepare(database, sql.c_str(), -1, &stmt, NULL);
    int rcAddict;
    if (rc != SQLITE_OK) {
        this->raisedError = true;
        this->dbError = "sql.errCreate";
        this->details = (char*)sqlite3_errmsg(database);

        return false;
    }
    else {
        rc = sqlite3_step(stmt);
        int rowCount = 0;
        while (rc != SQLITE_DONE && rc != SQLITE_OK) {
            rowCount++;
            int colCount = sqlite3_column_count(stmt);
            if (colCount == 0) {
                this->raisedError = true;
                this->dbError = "sql.errCreate";
                this->details = "no such table";
                return false;
            }
            for (int colIndex = 0; colIndex < colCount; colIndex++) {
                int type = sqlite3_column_type(stmt, colIndex);
                sqlite3_stmt *stmtRes = NULL;
                const char * columnName = sqlite3_column_name(stmt, colIndex);
                if (type == SQLITE_TEXT) {
                    //return true;
                    const unsigned char * idExported = sqlite3_column_text(stmt, colIndex);
                    //return true;
                    std::string stringId( reinterpret_cast< char const* >(idExported) ) ;
                    sql = "SELECT id FROM users WHERE id='" + stringId + "'";
                    int a = SQLITE_OK;
                    rcAddict = sqlite3_prepare(database, sql.c_str(), -1, &stmtRes, NULL);
                    if (rcAddict != SQLITE_OK) {
                        this->raisedError = true;
                        this->dbError = "sql.errCreate";
                        this->details = (char*)sqlite3_errmsg(database);
                        return false;
                    }
                    else {
                        rcAddict = sqlite3_step(stmtRes);
                        int addictRowCount = 0;
                        while (rc != SQLITE_DONE && rc != SQLITE_OK) {
                            addictRowCount++;
                            //int addictColCount = sqlite3_column_count(stmtRes);
                            return sqlite3_column_type(stmtRes, 0) != SQLITE_NULL;
                        }
                        if (rc != SQLITE_DONE) {
                            this->raisedError = true;
                            this->dbError = "sql.errCreate";
                            return false;
                        }
                    }
                }
                else return false;
            }
            rc = sqlite3_step(stmt);
        }
        if (rc != SQLITE_DONE) {
            this->raisedError = true;
            this->dbError = "sql.errCreate";
            this->details = (char*)sqlite3_errmsg(database);

            return false;
        }
    }
    return false;
}

DatabaseAppInterface::~DatabaseAppInterface () {
    sqlite3_close(database);
    //delete database;
}
