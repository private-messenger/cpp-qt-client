#include "cryptography.h"
#include <cstring>

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

AES256::AES256 (unsigned char* data) {
    this->privatekey = data;
    this->publickey = data;
}

unsigned char* AES256::encode (unsigned char *data) {
    std::string scriptPath = "nodejs_tools/cryptography/aes-encode.js ";
    std::string key = (char*)this->privatekey;
    std::string dataStr = (char*)data;
    std::string command = scriptPath + key + " " + dataStr;
    qDebug((char*)command.c_str());
    unsigned char* result = (unsigned char*)nodejsRun((char*)command.c_str()).data();
    qDebug((char*)result);
    return result;
}

unsigned char* AES256::decode (unsigned char *data) {
    return data;
}

RSA::RSA (unsigned char* publickey, unsigned char* privkey) {
    if (!publickey || !privatekey) {
        this->generateKeys();
    }
    else {
        this->publickey = publickey;
        this->privatekey = privkey;
    }
}

void RSA::generateKeys () {
    // (!) Добавить НОРМАЛЬНУЮ генерацию ключей
    this->publickey = (unsigned char*)"PUBLIC RSA KEY";
    this->privatekey = (unsigned char*)"PRIVATE RSA KEY";
}

unsigned char* RSA::encode (unsigned char *data) {
    // (!) Добавить НОРМАЛЬНОЕ шифрование по алгоритму RSA
    return data;
}

unsigned char* RSA::decode (unsigned char *data) {
    // (!) Добавить НОРМАЛЬНОЕ шифрование по алгоритму RSA
    return data;
}
