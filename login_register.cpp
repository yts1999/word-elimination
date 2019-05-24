#include "login_register.h"
#include "ui_login_register.h"
#include <QDesktopWidget>

Login_Register::Login_Register(QWidget *parent, UserDatabase *_userdb) :
    QWidget(parent), ui(new Ui::Login_Register), lw(this, _userdb), rw(this, _userdb) {
    ui->setupUi(this);
    switch_to_login();
    setFixedSize(500, 400);
    move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 2);
    connect(&lw, SIGNAL(toRegister()), this, SLOT(switch_to_register()));
    connect(&rw, SIGNAL(toLogin()), this, SLOT(switch_to_login()));
    connect(&lw, SIGNAL(toMainWindow()), this, SLOT(switch_to_MainWindow()));
}

Login_Register::~Login_Register()
{
    delete ui;
}

void Login_Register::switch_to_login() {
    setWindowTitle("登录");
    rw.hide();
    lw.refresh();
    lw.show();
}

void Login_Register::switch_to_register() {
    setWindowTitle("注册");
    lw.hide();
    rw.refresh();
    rw.show();
}

void Login_Register::switch_to_MainWindow() {
    close();
    emit toMainWindow();
}
