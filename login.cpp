#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login) {
    ui->setupUi(this);
}

Login::~Login() {
    delete ui;
}

void Login::on_loginButton_clicked() {
    QString usr = ui->userName->text(), pwd = ui->passWord->text();
    if (usr == "")
        QMessageBox::warning(this,"错误","请输入用户名！");
    else
        if (pwd == "")
            QMessageBox::warning(this,"错误","请输入密码！");
        else {
        }
}
