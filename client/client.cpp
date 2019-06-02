#include "client.h"
#include <QHostAddress>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>

Client::Client() { //初始化客户端，设定端口并等待连接
    client.connectToHost(QHostAddress::LocalHost, 3482);
    client.waitForConnected();
}

Client::~Client() {}

void Client::send_data(QJsonObject data) { //发送一个JSON类
    if (client.state() != QTcpSocket::ConnectedState) {
        QMessageBox::critical(nullptr, "错误", "连接服务器错误！");
        exit(0);
    }
    client.write(QJsonDocument(data).toJson());
    client.flush();
    client.waitForBytesWritten();
}

QJsonObject Client::receive_data() { //接收一个JSON类
    client.waitForReadyRead();
    return QJsonDocument::fromJson(client.readAll()).object();
}

int Client::check_usr_pwd(QString usr, QString pwd) { //检查用户名密码的数据发送与接收
    QJsonObject obj;
    obj.insert("type", 0);
    obj.insert("usr", usr);
    obj.insert("pwd", pwd);
    send_data(obj);
    obj = receive_data();
    return obj.value("res").toInt();
}

bool Client::add_usr(QString usr, QString pwd, QString name, int usrtype) { //添加用户的数据发送与接收
    QJsonObject obj;
    obj.insert("type", 1);
    obj.insert("usr", usr);
    obj.insert("pwd", pwd);
    obj.insert("name", name);
    obj.insert("usrtype", usrtype);
    send_data(obj);
    obj = receive_data();
    return obj.value("res").toBool();
}

Userdata Client::get_usr_info(QString usr) { //获取用户信息的数据发送与接收
    QJsonObject obj;
    obj.insert("type", 2);
    obj.insert("usr", usr);
    send_data(obj);
    obj = receive_data();
    return Userdata(obj.value("usr").toString(), obj.value("pwd").toString(), obj.value("nickname").toString(), obj.value("usrtype").toInt(), obj.value("cp_num").toInt(), obj.value("exp").toInt(), obj.value("level").toInt());
}

bool Client::update_usr_info(Userdata usr) { //更新用户信息的数据发送与接收，由于只更新后三个信息，因此部分信息不必要发
    QJsonObject obj;
    obj.insert("type", 3);
    obj.insert("usr", usr.usr);
    //obj.insert("pwd", usr.pwd);
    //obj.insert("nickname", usr.nickname);
    obj.insert("usrtype", usr.usrtype);
    obj.insert("cp_num", usr.cp_num);
    obj.insert("exp", usr.exp);
    obj.insert("level", usr.level);
    send_data(obj);
    obj = receive_data();
    return obj.value("res").toBool();
}

bool Client::add_word(QString word) { //添加单词的数据发送与接收
    QJsonObject obj;
    obj.insert("type", 4);
    obj.insert("word", word);
    send_data(obj);
    obj = receive_data();
    return obj.value("res").toBool();
}

QString Client::get_word(int level) { //根据关卡号获取单词的数据发送与接收
    QJsonObject obj;
    obj.insert("type", 5);
    obj.insert("level", level);
    send_data(obj);
    obj = receive_data();
    return obj.value("res").toString();
}

void Client::table_query(QStandardItemModel *model, int usrtype, QString cond) { //用户信息查询表格的数据发送与接收，存入model，筛选条件cond
    QJsonObject obj;
    obj.insert("type", 6);
    obj.insert("cond", cond);
    obj.insert("usrtype", usrtype);
    send_data(obj);
    obj = receive_data();
    model->clear(); //清空表格
    int n = obj.value("num").toInt();
    if (usrtype == 0) { //闯关者表格
        model->setColumnCount(5); //重新设置表格
        model->setRowCount(n);
        model->setHeaderData(0, Qt::Horizontal, "用户名");
        model->setHeaderData(1, Qt::Horizontal, "昵称");
        model->setHeaderData(2, Qt::Horizontal, "挑战关卡数");
        model->setHeaderData(3, Qt::Horizontal, "经验值");
        model->setHeaderData(4, Qt::Horizontal, "等级");
        for (int i = 0; i < n; i++) { //填入接收到的数据
            model->setItem(i, 0, new QStandardItem(obj.value(QString("usr%1").arg(i)).toString()));
            model->setItem(i, 1, new QStandardItem(obj.value(QString("name%1").arg(i)).toString()));
            model->setItem(i, 2, new QStandardItem(QString("%1").arg(obj.value(QString("cp_num%1").arg(i)).toInt())));
            model->setItem(i, 3, new QStandardItem(QString("%1").arg(obj.value(QString("exp%1").arg(i)).toInt())));
            model->setItem(i, 4, new QStandardItem(QString("%1").arg(obj.value(QString("level%1").arg(i)).toInt())));
        }
    }
    else { //出题者表格
        model->setColumnCount(4); //重新设置表格
        model->setRowCount(n);
        model->setHeaderData(0, Qt::Horizontal, "用户名");
        model->setHeaderData(1, Qt::Horizontal, "昵称");
        model->setHeaderData(2, Qt::Horizontal, "出题数");
        model->setHeaderData(3, Qt::Horizontal, "等级");
        for (int i = 0; i < n; i++) { //填入接收到的数据
            model->setItem(i, 0, new QStandardItem(obj.value(QString("usr%1").arg(i)).toString()));
            model->setItem(i, 1, new QStandardItem(obj.value(QString("name%1").arg(i)).toString()));
            model->setItem(i, 2, new QStandardItem(QString("%1").arg(obj.value(QString("cp_num%1").arg(i)).toInt())));
            model->setItem(i, 3, new QStandardItem(QString("%1").arg(obj.value(QString("level%1").arg(i)).toInt())));
        }
    }
}

bool Client::logout(QString usr) {
    QJsonObject obj;
    obj.insert("type", 7);
    obj.insert("usr", usr);
    send_data(obj);
    obj = receive_data();
    return obj.value("res").toBool();
}
