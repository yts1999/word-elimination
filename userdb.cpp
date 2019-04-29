#include <QString>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

void userdb_init() {
    QSqlDatabase userdb = QSqlDatabase::addDatabase("QSQLITE","users");
    userdb.setHostName("localhost");
    userdb.setDatabaseName("users.db");
    if (! userdb.open()) {
        QMessageBox::critical(nullptr, "错误", "连接错误！");
    }
    else {
        QSqlQuery user(userdb);
        user.exec("create table user(name varchar(10) primary key, passwd varchar(10))");
    }
}
