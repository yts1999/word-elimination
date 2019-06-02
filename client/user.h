#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>

class User : public QObject {
    Q_OBJECT

public:
    User();
    ~User();
    QString get_name() const;
    QString get_nickname() const;
    virtual int get_usrtype() const = 0;
    int get_level() const;
    void inc_level();

signals:
    void modifyed();

protected:
    QString name, password, nickname;
    int level;
};

#endif // USER_H
