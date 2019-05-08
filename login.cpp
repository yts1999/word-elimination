#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QRegExpValidator>

Login::Login(QWidget *parent, UserDatabase *_userdb) :
    QWidget(parent), ui(new Ui::Login), userdb(_userdb) {
    ui->setupUi(this);
    //使用正则表达式限定输入格式
    ui->userName->setValidator(new QRegExpValidator(QRegExp("^[A-Za-z0-9_]{1,10}$"), this));
    ui->passWord->setValidator(new QRegExpValidator(QRegExp("^.{1,20}$"), this));
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
        QMessageBox::warning(this, "提示", "请输入用户名！");
    else
        if (pwd == "")
            QMessageBox::warning(this, "提示", "请输入密码！");
        else {
            int flag = userdb->check_usr_pwd(usr,pwd);
            if (flag == 1)
                QMessageBox::warning(this, "提示", "该用户不存在！");
            else
                if (flag == 2)
                    QMessageBox::warning(this, "提示", "密码错误！");
        }
}

void Login::on_registerButton_clicked() {
    emit toRegister();
}
