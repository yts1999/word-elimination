#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QRegExpValidator>

Login::Login(QWidget *parent, Client *_client) :
    QWidget(parent), ui(new Ui::Login), client(_client) {
    ui->setupUi(this);
    //使用正则表达式限定输入格式
    ui->userName->setValidator(new QRegExpValidator(QRegExp("^[A-Za-z0-9_]{0,10}$"), this));
    ui->passWord->setValidator(new QRegExpValidator(QRegExp("^.{0,20}$"), this));
}

Login::~Login() {
    delete ui;
}

void Login::refresh() {
    ui->userName->clear();
    ui->passWord->clear();
}

void Login::on_loginButton_clicked() {
    QString usr = ui->userName->text(), pwd = ui->passWord->text(); //获取输入的用户名和密码
    if (usr == "")
        QMessageBox::warning(this, "提示", "请输入用户名！");
    else
        if (pwd == "")
            QMessageBox::warning(this, "提示", "请输入密码！");
        else {
            int flag = client->check_usr_pwd(usr,pwd); //进行用户名密码校验
            if (flag == 1)
                QMessageBox::warning(this, "提示", "该用户不存在！");
            else
                if (flag == 2)
                    QMessageBox::warning(this, "提示", "密码错误！");
                else
                    if (flag == 3)
                        QMessageBox::warning(this, "提示", "该用户已登录！");
                    else
                        emit toMainWindow(usr); //用户名密码校验正确，切换到主窗口
        }
}

void Login::on_registerButton_clicked() {
    emit toRegister();
}

void Login::on_passWord_returnPressed() {
    on_loginButton_clicked();
}
