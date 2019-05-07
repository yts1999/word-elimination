#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

Login::Login(QWidget *parent, UserDatabase *_userdb) :
    QWidget(parent), ui(new Ui::Login), userdb(_userdb) {
    ui->setupUi(this);
}

Login::~Login() {
    delete ui;
}

void Login::refresh() {
    ui->userName->clear();
    ui->passWord->clear();
}

void Login::on_loginButton_clicked() {
    QString usr = ui->userName->text(), pwd = ui->passWord->text();
    if (usr == "")
        QMessageBox::warning(this,"错误","请输入用户名！");
    else
        if (pwd == "")
            QMessageBox::warning(this,"错误","请输入密码！");
        else {
            int flag = userdb->check_usr_pwd(usr,pwd);
            if (flag == 1)
                QMessageBox::warning(this,"错误","该用户不存在！");
            else
                if (flag == 2)
                    QMessageBox::warning(this,"错误","密码错误！");
        }
}

void Login::on_registerButton_clicked() {
    emit toRegister();
}
