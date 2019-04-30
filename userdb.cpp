#include "userdb.h"
#include <QString>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

UserDatabase::UserDatabase() {
    userdb = QSqlDatabase::addDatabase("QSQLITE","userdb");
    userdb.setHostName("localhost");
    userdb.setDatabaseName("users.db");
    if (! userdb.open()) {
        QMessageBox::critical(nullptr, "错误", "连接错误！");
    }
    else {
        QSqlQuery userdb_create(userdb);
        userdb_create.exec("create table user(name varchar(10) primary key, passwd varchar(10))");
    }
}

UserDatabase::~UserDatabase() {
    userdb.close();
    userdb.removeDatabase("userdb");
}

int UserDatabase::check_usr_pwd(QString usr,QString pwd) {
    QSqlQuery userdb_query(userdb);
    userdb_query.exec(QString("select * from user where name=='%1'").arg(usr));
    if (! userdb_query.first())
        return 1;
    else
        if (userdb_query.value(1).toString() == pwd)
            return 0;
        else
            return 2;
}
