#ifndef LOGIN_REGISTER_H
#define LOGIN_REGISTER_H

#include "login.h"
#include "register.h"
#include <QWidget>

namespace Ui {
class Login_Register;
}

class Login_Register : public QWidget
{
    Q_OBJECT

public:
    explicit Login_Register(QWidget *parent = nullptr, UserDatabase *_userdb = nullptr);
    ~Login_Register();

signals:
    void toMainWindow(QString);

private slots:
    void switch_to_login();
    void switch_to_register();
    void switch_to_MainWindow(QString usrname);

private:
    Ui::Login_Register *ui;
    Login lw;
    Register rw;
};

#endif // LOGIN_REGISTER_H
