#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QThread>
#include "nodejs-run.h"
// Формы
#include "create-chat.h"
#include "credits.h"
#include "log_in_form.h"
#include "databaseAI.h"
#include "create-process.h"
#include "freenet_settings.h"
#include "i2p_settings.h"
#include "ch_lang.h"
#include "key-viewer.h"
#include "general_settings.h"
#include "add-contact.h"

using std::vector;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;}
QT_END_NAMESPACE

class MessageUpdater : public QThread {
    Q_OBJECT
public:
    MessageUpdater (QString messagesMd5, QObject* parent = nullptr) : QThread(parent) {
        this->messagesMd5 = messagesMd5;
    }
    bool messageEdited = false;
signals:
    void finished();
protected:
    void run() override
    {
        // Выполняем функцию в потоке
        QString currentMessagesMd5 = QString(nodejsRun("nodejs_tools/database/get-messages-md5.js"));
        this->messageEdited = currentMessagesMd5 != this->messagesMd5;
        if (currentMessagesMd5 != this->messagesMd5) {
            this->messagesMd5 = currentMessagesMd5;
        }

        // Завершаем поток и отправляем сигнал
        emit finished();
    }
private:
    QString messagesMd5;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showLogIn ();
    bool needAuth = false;
    bool isAuthed ();
    bool error = false;
    bool needSetupLocale = false;
    void setupLocale (std::string locale);
    void startServer ();
    void chooseLocale ();
    void clearInterface ();
    void reloadMessages ();
    DatabaseAppInterface database;

protected slots:
    void autoscale ();
    void dynamicAccess ();

private slots:
    void creditsActionClicked();
    void freenetSettingsClicked();
    void settingsI2pActionClicked();
    void logoutActionClicked();
    void generalSettingsActionClicked();
    void onThreadMessagesFinished();
    void saveAccountOnFile ();

    void reloadForm ();
    void on_keysList_itemDoubleClicked(QListWidgetItem *item);
    void on_contactList_itemDoubleClicked(QListWidgetItem *item);
    void on_addContact_clicked();
    void on_updatePas_clicked();
    void on_messagesField_itemClicked(QListWidgetItem *item);
    void on_sendButton_clicked();
    /* Переводчик */

    void setupLang_ru_RU ();
    void setupLang_en_UK ();
    void setupLang_ua_UA ();
    void setupLang_pl_PL ();

    void on_removeContact_clicked();

    void on_setLogin_clicked();

private:
    void initInterface ();
    int lastTimeUpdated = 0;
    vector<vector<QString>> contacts      = {};
    vector<vector<QString>> keys          = {};
    QString                 login         = "";
    QString                 id            = "";
    QString                 b32i2paddress = "";
    QString                 messagesMd5   = "";
    std::map<QString, vector<QString>> messages {};
    vector<QString> messageKeys {};
    MessageUpdater* messageUpdaterThread;
    //QObject*        messageUpdate;

    std::string locale = "ru_RU";
    Ui::MainWindow *ui;
    QTimer *timerScale;
    QTimer *timerAccess;
    bool serverRunned = false;
    // "Дочерние" окна
    Credits credits;
    LogInForm logInForm;
    StartProcess server;
    FreenetSettings freenetSettings;
    I2pSettings i2pSettings;
    KeyViewer keyViewer;
    GeneralSettings generalSettings;
    CreateChat createChat;
    AddContact addContact;
};
#endif // MAINWINDOW_H
