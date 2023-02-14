#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

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


class Cryptography {
public:
    // Cryptography();
    unsigned char* publickey = 0;
    unsigned char* privatekey = 0;
    virtual unsigned char* encode (unsigned char* data) = 0;
    virtual unsigned char* decode (unsigned char* data) = 0;
};

class AES256 : public Cryptography {
public:
    AES256 (unsigned char* key);
    /*unsigned char* publickey = 0;
    unsigned char* privatekey = 0;*/
};

#endif // CRYPTOGRAPHY_H
