#ifndef USERDB_H
#define USERDB_H

#include <QSqlDatabase>
#include <QString>

class UserDatabase : private QSqlDatabase {
public:
       UserDatabase();
       ~UserDatabase();
       int check_usr_pwd(const QString &usr,const QString &pwd) const; //返回0表示正确，返回1表示用户名错误，返回2表示密码错误

};

#endif // USERDB_H
