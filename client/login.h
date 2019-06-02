#ifndef LOGIN_H
#define LOGIN_H

#include "client.h"
#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget {
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr, Client *_client = nullptr);
    ~Login();
    void refresh();

signals:
    void toRegister();
    void toMainWindow(QString usrname);

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();

    void on_passWord_returnPressed();

private:
    Ui::Login *ui;
    Client *client;
};

#endif // LOGIN_H
