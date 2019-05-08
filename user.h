#ifndef USER_H
#define USER_H

#include <QString>

class User {
public:
    User(const QString &_name = "", const QString &_password = "", const QString &_nickname = "", const int &_level = 1);
    QString get_name() const;
    QString get_nickname() const;
    int get_level() const;
    void inc_level();

private:
    QString name, password, nickname;
    int level;
};

#endif // USER_H
