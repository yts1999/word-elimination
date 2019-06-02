#ifndef SERVER_H
#define SERVER_H

#include "userdb.h"
#include "worddb.h"
#include <QTcpServer>
#include <QObject>
#include <QJsonObject>
#include <QString>
#include <set>

class Server : public QObject {
    Q_OBJECT

public:
    explicit Server(UserDatabase *_userdb = nullptr, WordDatabase *_worddb = nullptr);
    ~Server();

private slots:
    void new_connect();
    void break_connect();
    void recieve_request();

private:
    QJsonObject check_usr_pwd(QJsonObject obj);
    QJsonObject add_usr(QJsonObject obj);
    QJsonObject get_usr_info(QJsonObject obj);
    QJsonObject update_usr_info(QJsonObject obj);
    QJsonObject add_word(QJsonObject obj);
    QJsonObject get_word(QJsonObject obj);
    QJsonObject table_query(QJsonObject obj);
    QJsonObject logout(QJsonObject obj);
    QTcpServer server;
    UserDatabase *userdb;
    WordDatabase *worddb;
    std::set<QString> online_user;
};

#endif // SERVER_H
