#include "login_register.h"
#include "ui_login_register.h"

Login_Register::Login_Register(QWidget *parent) :
    QWidget(parent), ui(new Ui::Login_Register), lw(this), rw(this) {
    ui->setupUi(this);
    switch_to_login();
}

Login_Register::~Login_Register()
{
    delete ui;
}

void Login_Register::switch_to_login() {
    setWindowTitle("登录");
    rw.hide();
    lw.show();
}

void Login_Register::switch_to_register() {
    setWindowTitle("注册");
    lw.hide();
    rw.show();
}
