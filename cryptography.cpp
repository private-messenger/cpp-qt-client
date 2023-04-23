#include "cryptography.h"
#include <cstring>

#include "nodejs-run.h"

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
