#ifndef DATABASEAPPINTERFACE_H
#define DATABASEAPPINTERFACE_H

//#include "sqlite3.h"
#include <string>

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

/*class SQLite3_interface {
public:
    SQLite3_interface (sqlite3* database) {
        this->database = database;
    }
    ~SQLite3_interface () {
        //delete this->database;
    }

    bool signleSet (char* table, int type, char* key, char* value, int whereType, char* whereKey, char* whereValue) {
        std::string sqlReq = "UPDATE " + std::string(table) + " SET " + std::string(key) + " = ? WHERE "+whereKey+" = ?";
        sqlite3_stmt *stmt = NULL;
        int rc = sqlite3_prepare_v2(database, sqlReq.c_str(), -1, &stmt, NULL);
        if (rc == SQLITE_ERROR) {
            return false;
        }
        sqlite3_reset(stmt);
        switch (type) {
            case SQLITE_TEXT :
                sqlite3_bind_text(stmt, 1, value, -1, SQLITE_STATIC);
                break;
            case SQLITE_FLOAT :
                sqlite3_bind_double(stmt, 1, (double)atof(value));
                break;
            case SQLITE_INTEGER :
                sqlite3_bind_int(stmt, 1, (int)atof(value));
                break;
            case SQLITE_NULL :
                sqlite3_bind_null(stmt, 1);
                break;
            default :
                sqlite3_bind_blob(stmt, 1, value, -1, SQLITE_STATIC);
                break;
        }
        switch (whereType) {
            case SQLITE_TEXT :
                sqlite3_bind_text(stmt, 2, whereValue, -1, SQLITE_STATIC);
                break;
            case SQLITE_FLOAT :
                sqlite3_bind_double(stmt, 2, (double)atof(whereValue));
                break;
            case SQLITE_INTEGER :
                sqlite3_bind_int(stmt, 2, (int)atof(whereValue));
                break;
            case SQLITE_NULL :
                sqlite3_bind_null(stmt, 2);
                break;
            default :
                sqlite3_bind_blob(stmt, 2, whereValue, -1, SQLITE_STATIC);
                break;
        }
        rc = sqlite3_step(stmt);
        sqlite3_clear_bindings(stmt);
        if (rc == SQLITE_ERROR) {
            return false;
        }
        else {
            return true;
        }
    }
private:
    sqlite3* database = 0;
};*/

class DatabaseAppInterface
{
public:
    DatabaseAppInterface();
    ~DatabaseAppInterface ();
    bool raisedError = false;
    char *dbError = 0;
    char* details = "-";
    bool getAuthed ();
    bool hasAccount (char* accountId);
    bool reg (std::string login, std::string password);
    void setValue (char* key, char* value);
private:
    //sqlite3* database = 0;
    //SQLite3_interface sql = 0;
};

#endif // DATABASEAPPINTERFACE_H
