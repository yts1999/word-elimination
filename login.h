#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "userdb.h"

namespace Ui {
class Login;
}

class Login : public QDialog {
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_loginButton_clicked();

private:
    Ui::Login *ui;
    UserDatabase userdb;
};

#endif // LOGIN_H
