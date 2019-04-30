#include "userdb.h"
#include <QString>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

UserDatabase::UserDatabase() :
    QSqlDatabase (addDatabase("QSQLITE", "userdb")) {
        setHostName("localhost");
        setDatabaseName("users.db");
        if (! open()) {
            QMessageBox::critical(nullptr, "错误", "连接错误！");
        }
        else {
            QSqlQuery userdb_create(*this);
            userdb_create.exec("create table user(name varchar(10) primary key, passwd varchar(10))");
        }
    }

UserDatabase::~UserDatabase() {
    close();
    removeDatabase("userdb");
}

int UserDatabase::check_usr_pwd(const QString &usr,const QString &pwd) const {
    QSqlQuery userdb_query(*this);
    userdb_query.exec(QString("select * from user where name=='%1'").arg(usr));
    if (! userdb_query.first())
        return 1;
    else
        if (userdb_query.value(1).toString() == pwd)
            return 0;
        else
            return 2;
}
