#ifndef LOGIN_H
#define LOGIN_H

#include "userdb.h"
#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void toRegister();

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();

private:
    Ui::Login *ui;
    UserDatabase userdb;
};

#endif // LOGIN_H
