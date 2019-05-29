#include "userdb.h"
#include "player.h"
#include "manager.h"
#include <QString>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

UserDatabase::UserDatabase() :
    QSqlDatabase(addDatabase("QSQLITE", "userdb")) {
        setHostName("localhost");
        setDatabaseName("users.db");
        if (! open())
            QMessageBox::critical(nullptr, "错误", "连接错误！");
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
    userdb_query.exec(QString("insert into user values('%1','%2','%3','%4','0','0','1')").arg(usr).arg(pwd).arg(name).arg(usrtype == -2?0:1));
}

int UserDatabase::get_usr_type(const QString &usr) const {
    QSqlQuery userdb_query(*this);
    userdb_query.exec(QString("select * from user where name=='%1'").arg(usr));
    if (! userdb_query.first())
        return -1;
    return userdb_query.value(3).toInt();
}

void UserDatabase::modify_cp_num(const QString &usr, const int &cp_num) {
    QSqlQuery userdb_query(*this);
    userdb_query.exec(QString("update user set cp_num = '%1' where name == '%2'").arg(cp_num).arg(usr));
}

void UserDatabase::modify_exp(const QString &usr, const int &exp) {
    QSqlQuery userdb_query(*this);
    userdb_query.exec(QString("update user set exp = '%1' where name == '%2'").arg(exp).arg(usr));
}

void UserDatabase::modify_level(const QString &usr, const int &level) {
    QSqlQuery userdb_query(*this);
    userdb_query.exec(QString("update user set level = '%1' where name == '%2'").arg(level).arg(usr));
}
