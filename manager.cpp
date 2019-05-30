#include "manager.h"
#include <QVariant>
#include <QSqlQuery>

Manager::Manager(UserDatabase *_userdb, QString _name) : //从数据库中根据用户名查询用户信息
    User(_userdb, _name), probnum(0) {
    QSqlQuery userdb_query(*userdb);
    userdb_query.exec(QString("select * from user where name=='%1'").arg(name));
    if (! userdb_query.first())
        return;
    password = userdb_query.value(1).toString();
    nickname = userdb_query.value(2).toString();
    probnum = userdb_query.value(4).toInt();
    level = userdb_query.value(6).toInt();
}

Manager::~Manager() {}

int Manager::get_usrtype() const { //用户类型
    return 1;
}

int Manager::get_probnum() const { //出题数目
    return probnum;
}

void Manager::inc_probnum() { //增加出题数目
    probnum++;
    userdb->modify_cp_num(name, probnum); //修改数据库信息
    emit modifyed();
}
