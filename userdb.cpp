#include "userdb.h"
#include <QString>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

UserDatabase::UserDatabase() :
    QSqlDatabase(addDatabase("QSQLITE", "userdb")) {
        setHostName("localhost");
        setDatabaseName("users.db");
        if (! open()) {
            QMessageBox::critical(nullptr, "错误", "连接错误！");
        }
        else {
            QSqlQuery userdb_create(*this);
            userdb_create.exec("create table user(name varchar(10) primary key, passwd varchar(20), "
                               "nickname varchar(20), type tinyint, cp_num int, exp int, level int)");
        }
    }

UserDatabase::~UserDatabase() {
    close();
    removeDatabase("userdb");
}

bool UserDatabase::check_usr(const QString &usr) const {
    QSqlQuery userdb_query(*this);
    userdb_query.exec(QString("select * from user where name=='%1'").arg(usr));
    return userdb_query.first();
}

int UserDatabase::check_usr_pwd(const QString &usr, const QString &pwd) const {
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

void UserDatabase::add_usr(const QString &usr, const QString &pwd, const QString &name, const int &usrtype) {
    QSqlQuery userdb_query(*this);
    userdb_query.exec(QString("insert into user values('%1','%2','%3','%4','0','0','1')").arg(usr).arg(pwd).arg(name).arg(usrtype));
}
