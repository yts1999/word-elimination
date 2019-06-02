#ifndef CLIENT_H
#define CLIENT_H

#include "userdata.h"
#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>
#include <QString>
#include <QStandardItemModel>

class Client : public QObject {
    Q_OBJECT
public:
    Client();
    ~Client();
    int check_usr_pwd(QString usr, QString pwd);
    bool add_usr(QString usr, QString pwd, QString name, int usrtype);
    Userdata get_usr_info(QString usr);
    bool update_usr_info(Userdata usr);
    bool add_word(QString word);
    QString get_word(int level);
    void table_query(QStandardItemModel *model, int usrtype, QString cond);
    bool logout(QString usr);

private:
    void send_data(QJsonObject data);
    QJsonObject receive_data();
    QTcpSocket client;
};

#endif // CLIENT_H
