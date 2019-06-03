#include "server.h"
#include "userdb.h"
#include "worddb.h"
#include <iostream>
#include <QTcpSocket>
#include <QTcpServer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QSqlRecord>
#include <QSqlTableModel>

Server::Server(UserDatabase *_userdb, WordDatabase *_worddb) : //服务器初始化
    userdb(_userdb), worddb(_worddb) {
    std::cout << "============ Word Elimination Game Server ============\n";
    std::cout << "Designed by Tianshu Yu, yts1999@bupt.edu.cn\n";
    connect(&server, SIGNAL(newConnection()), this, SLOT(new_connect()));
    if (! server.listen(QHostAddress::Any, 3482)) { //监听端口
        std::cout << "Fail to listen\n";
        exit(1);
    }
    std::cout << "Listen to Port 3482\n";
}

Server::~Server() {}

void Server::new_connect() { //新的客户端连接到服务器
    QTcpSocket *con = server.nextPendingConnection();
    connect(con, SIGNAL(readyRead()), this, SLOT(recieve_request()));
    connect(con, SIGNAL(disconnected()), this, SLOT(break_connect()));
    std::cout << "Establish new connection with client " << con->peerAddress().toString().toStdString() << "\n";
}

void Server::break_connect() { //断开连接
    std::cout << "Break client connection\n";
}

void Server::recieve_request() { //收到来自客户端的请求
    QTcpSocket *sender = dynamic_cast<QTcpSocket *>(QObject::sender()); //获取发送请求的客户端
    std::cout << "Handle request from client " << sender->peerAddress().toString().toStdString() << "\n";
    QByteArray data = sender->readAll(); //接收数据
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    switch (obj.value("type").toInt()) { //根据发送数据中的类型来确定进行何种操作
    case 0: //校验用户名密码
        std::cout << "Check user & password\n";
        sender->write(QJsonDocument(check_usr_pwd(obj)).toJson());
        break;

    case 1: //添加用户
        std::cout << "Add user\n";
        sender->write(QJsonDocument(add_usr(obj)).toJson());
        break;

    case 2: //获取用户信息
        std::cout << "Get user information\n";
        sender->write(QJsonDocument(get_usr_info(obj)).toJson());
        break;

    case 3: //更新用户信息
        std::cout << "Update user information\n";
        sender->write(QJsonDocument(update_usr_info(obj)).toJson());
        break;

    case 4: //添加单词
        std::cout << "Add a word\n";
        sender->write(QJsonDocument(add_word(obj)).toJson());
        break;

    case 5: //获取单词
        std::cout << "Get a word for client\n";
        sender->write(QJsonDocument(get_word(obj)).toJson());
        break;

    case 6: //用户记录查询
        std::cout << "Get table for client\n";
        sender->write(QJsonDocument(table_query(obj)).toJson());
        break;

    case 7: //用户注销
        std::cout << "Client logout\n";
        sender->write(QJsonDocument(logout(obj)).toJson());
    }
    sender->flush();
    std::cout << "Handle request completed\n";
}


QJsonObject Server::check_usr_pwd(QJsonObject obj) { //校验用户名密码
    QString usr = obj.value("usr").toString(), pwd = obj.value("pwd").toString();
    int res = userdb->check_usr_pwd(usr, pwd);
    if (res == 0) {
        if (online_user.count(usr)) //用户已经登录
            res = 3;
        else
            online_user.insert(usr); //在已登录列表中添加用户
    }
    QJsonObject resobj;
    resobj.insert("res", res);
    return resobj;
}

QJsonObject Server::add_usr(QJsonObject obj) { //添加用户
    QString usr = obj.value("usr").toString(), pwd = obj.value("pwd").toString(), name = obj.value("name").toString();
    int usrtype = obj.value("usrtype").toInt();
    bool res = 0;
    if (userdb->check_usr(usr))
        res = 0;
    else {
        res = 1;
        userdb->add_usr(usr, pwd, name, usrtype);
    }
    QJsonObject resobj;
    resobj.insert("res", res);
    return resobj;
}

QJsonObject Server::get_usr_info(QJsonObject obj) { //获取用户信息
    QString usr = obj.value("usr").toString();
    QSqlRecord rec = userdb->get_usr_info(usr);
    QJsonObject resobj;
    resobj.insert("usr", rec.value(0).toString());
    resobj.insert("pwd", rec.value(1).toString());
    resobj.insert("nickname", rec.value(2).toString());
    resobj.insert("usrtype", rec.value(3).toInt());
    resobj.insert("cp_num", rec.value(4).toInt());
    resobj.insert("exp", rec.value(5).toInt());
    resobj.insert("level", rec.value(6).toInt());
    return resobj;
}

QJsonObject Server::update_usr_info(QJsonObject obj) { //更新用户信息
    QString usr = obj.value("usr").toString();
    int usrtype = obj.value("usrtype").toInt(), cp_num = obj.value("cp_num").toInt(), exp = obj.value("exp").toInt(), level = obj.value("level").toInt();
    if (usrtype == 0) { //闯关者，根据用户类型判定更新哪些信息
        userdb->modify_cp_num(usr, cp_num);
        userdb->modify_exp(usr, exp);
        userdb->modify_level(usr, level);
    }
    else { //出题者
        userdb->modify_cp_num(usr, cp_num);
        userdb->modify_level(usr, level);
    }
    QJsonObject resobj;
    resobj.insert("res", true);
    return resobj;
}

QJsonObject Server::add_word(QJsonObject obj) { //添加单词
    QString word = obj.value("word").toString();
    bool res = 0;
    if (worddb->check_word(word))
        res = 0;
    else {
        res = 1;
        worddb->add_word(word);
    }
    QJsonObject resobj;
    resobj.insert("res", res);
    return resobj;
}

QJsonObject Server::get_word(QJsonObject obj) { //获取单词
    int level = obj.value("level").toInt();
    QString res = worddb->get_word(level);
    QJsonObject resobj;
    resobj.insert("res", res);
    return resobj;
}

QJsonObject Server::table_query(QJsonObject obj) { //用户记录查询
    QString cond = obj.value("cond").toString();
    int usrtype = obj.value("usrtype").toInt();
    QSqlTableModel model(nullptr, *userdb);
    model.setTable("user");
    model.setFilter(cond);
    model.setSort(0, Qt::AscendingOrder);
    if (usrtype == 0) { //闯关者，根据用户类型选取需要的数据
        model.removeColumn(1);
        model.removeColumn(2);
    }
    else { //出题者
        model.removeColumn(1);
        model.removeColumn(2);
        model.removeColumn(3);
    }
    model.select();
    QJsonObject resobj;
    int n = model.rowCount();
    resobj.insert("num", n);
    if (usrtype == 0) //闯关者，根据用户类型将数据插入JSON类
        for (int i = 0; i < n; i++) {
            resobj.insert(QString("usr%1").arg(i), model.record(i).value(0).toString());
            resobj.insert(QString("name%1").arg(i), model.record(i).value(1).toString());
            resobj.insert(QString("cp_num%1").arg(i), model.record(i).value(2).toInt());
            resobj.insert(QString("exp%1").arg(i), model.record(i).value(3).toInt());
            resobj.insert(QString("level%1").arg(i), model.record(i).value(4).toInt());
        }
    else //出题者
        for (int i = 0; i < n; i++) {
            resobj.insert(QString("usr%1").arg(i), model.record(i).value(0).toString());
            resobj.insert(QString("name%1").arg(i), model.record(i).value(1).toString());
            resobj.insert(QString("cp_num%1").arg(i), model.record(i).value(2).toInt());
            resobj.insert(QString("level%1").arg(i), model.record(i).value(3).toInt());
        }
    return resobj;
}

QJsonObject Server::logout(QJsonObject obj) { //用户注销
    QString usr = obj.value("usr").toString();
    online_user.erase(usr);
    QJsonObject resobj;
    resobj.insert("res", true);
    return resobj;
}
