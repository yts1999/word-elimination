#ifndef USERDB_H
#define USERDB_H

#include <QSqlDatabase>
#include <QString>

class UserDatabase {
public:
       UserDatabase();
       ~UserDatabase();
       int check_usr_pwd(QString usr,QString pwd); //返回0表示正确，返回1表示用户名错误，返回2表示密码错误

private:
       QSqlDatabase userdb;
};

#endif // USERDB_H
