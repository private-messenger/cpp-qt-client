#ifndef LOCALES_H
#define LOCALES_H
#include <string>

class Locales
{
public:
    Locales(std::string locale);
    std::string locale;
    std::string getLocaleVar (std::string key);
};

#endif // LOCALES_H
