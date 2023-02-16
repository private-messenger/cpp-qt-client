#include "locales.h"
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

Locales::Locales(std::string locale) {
    this->locale = locale;
}

std::string Locales::getLocaleVar (std::string key) {
    std::string wordvalue = "Ошибка локализации: ключ не найден. Не используйте бэта-версию переводов, либо обновите или переустановите программу.";
    // Основной перевод
    if (key == "prog.name") {
        wordvalue = "Система персонализированых индивидуальных ключей (СПИК)";
    }
    // Файловые события (file input-output (fio))
    else if (key == "fio.errorTitle") {
        wordvalue = "Ошибка открытия файлов";
    }
    // SQL
    else if (key == "sql.errCreate") {
        wordvalue = "Ошибка использования файла базы данных. Файл локальной базы данных либо отсутствует, либо повреждён. Переустановите программу.\n\nСистемный вывод: ";
    }
    // Переводы UI
    // Главная панель программы
    else if (key == "menu.mainw.main") {
        wordvalue = "Программа";
    }
    else if (key == "menu.mainw.account") {
        wordvalue = "Аккаунт";
    }
    else if (key == "menu.mainw.language") {
        wordvalue = "Язык";
    }
    else if (key == "menu.mainw.logout") {
        wordvalue = "Выйти из учётной записи";
    }
    else if (key == "menu.mainw.settings") {
        wordvalue = "Настройки";
    }
    else if (key == "menu.mainw.credits") {
        wordvalue = "Об авторе";
    }
    else if (key == "menu.mainw.logoutlater") {
        wordvalue = "Задать время автовыхода";
    }
    else if (key == "menu.mainw.logoutnow") {
        wordvalue = "Выйти сейчас";
    }
    else if (key == "menu.mainw.settings.general") {
        wordvalue = "Общие настройки";
    }
    else if (key == "menu.mainw.settings.i2p") {
        wordvalue = "Настройки i2p";
    }
    else if (key == "menu.mainw.settings.freenet") {
        wordvalue = "Настройки freenet";
    }
    else if (key == "menu.mainw.save") {
        wordvalue = "Сохранить";
    }
    // Tab-виджеты
    else if (key == "prog.tab.profile") {
        wordvalue = "Профиль";
    }
    else if (key == "prog.tab.messages") {
        wordvalue = "Сообщения";
    }
    else if (key == "prog.tab.storage") {
        wordvalue = "Хранилище";
    }
    // Текст-лейбелы
    else if (key == "labels.mainw.id") {
        wordvalue = "Ваш ID";
    }
    else if (key == "labels.mainw.i2pAdr") {
        wordvalue = "Ваш b32 адрес по i2p";
    }
    else if (key == "labels.mainw.login") {
        wordvalue = "Ваш логин";
    }
    else if (key == "labels.mainw.keys") {
        wordvalue = "Ключи";
    }
    else if (key == "labels.mainw.contacts") {
        wordvalue = "Контакты";
    }
    else if (key == "labels.mainw.messages") {
        wordvalue = "Сообщения";
    }
    else if (key == "labels.mainw.dialog") {
        wordvalue = "Чат";
    }
    else if (key == "labels.mainw.indev") {
        wordvalue = "В разработке";
    }
    // Элементы ввода
    else if (key == "input.mainw.id") {
        wordvalue = "Здесь мог бы быть ваш идентификатор";
    }
    else if (key == "input.mainw.i2pAdr") {
        wordvalue = "Здесь мог бы быть ваш адрес в сети i2p";
    }
    else if (key == "input.mainw.login") {
        wordvalue = "Здесь мог бы быть ваш логин";
    }
    // Кнопки
    else if (key == "button.mainw.setlogin") {
        wordvalue = "Изменить";
    }
    else if (key == "button.mainw.updpassword") {
        wordvalue = "Обновить пароль";
    }
    else if (key == "button.mainw.addcontact") {
        wordvalue = "Добавить";
    }
    else if (key == "button.mainw.rmcontact") {
        wordvalue = "Удалить";
    }
    else if (key == "button.mainw.sendmsg") {
        wordvalue = "Отправить";
    }
    // Об авторе
    else if (key == "credits.title") {
        wordvalue = "Об авторе";
    }
    else if (key == "credits.developed_by") {
        wordvalue = "Разработчик: ";
    }
    else if (key == "credits.developer_lname") {
        wordvalue = "Приходько";
    }
    else if (key == "credits.developer_fname") {
        wordvalue = "Никита";
    }
    else if (key == "credits.mit_license") {
        wordvalue = "Лицензия MIT";
    }
    // Авторизация
    else if (key == "auth.login") {
        wordvalue = "Логин";
    }
    else if (key == "auth.password") {
        wordvalue = "Пароль";
    }
    else if (key == "auth.tab.sign_in") {
        wordvalue = "Вход";
    }
    else if (key == "auth.tab.sign_up") {
        wordvalue = "Регистрация";
    }
    else if (key == "auth.title") {
        wordvalue = "Авторизация";
    }
    else if (key == "auth.sign_in.button") {
        wordvalue = "Войти";
    }
    else if (key == "auth.sign_in_file.button") {
        wordvalue = "Войти с файла";
    }
    else if (key == "auth.repeat_password") {
        wordvalue = "Повторить пароль, чтобы не забыть";
    }
    else if (key == "auth.sign_up.button") {
        wordvalue = "Зарегистрироваться";
    }
    else if (key == "auth.error") {
        wordvalue = "Ошибка авторизации";
    }
    else if (key == "auth.nomatch_passwords") {
        wordvalue = "Пароли не совпадают между собой";
    }
    else if (key == "auth.successful.label") {
        wordvalue = "Вы успешно авторизовались!";
    }
    else if (key == "auth.successful.title") {
        wordvalue = "Успех";
    }
    return wordvalue;
}
