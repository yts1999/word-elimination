#include "manager.h"
#include <QVariant>
#include <QSqlQuery>

Manager::Manager(UserDatabase *_userdb, QString _name) :
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

int Manager::get_usrtype() const {
    return 1;
}

int Manager::get_probnum() const {
    return probnum;
}

void Manager::inc_probnum() {
    probnum++;
    userdb->modify_cp_num(name, probnum);
    emit modifyed();
}
