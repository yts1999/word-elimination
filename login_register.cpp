#include "login_register.h"
#include "ui_login_register.h"
#include <QDesktopWidget>

Login_Register::Login_Register(QWidget *parent, UserDatabase *_userdb) :
    QWidget(parent), ui(new Ui::Login_Register), lw(this, _userdb), rw(this, _userdb) { //该窗口为登录注册的父窗口
    ui->setupUi(this);
    switch_to_login();
    setFixedSize(500, 400);
    move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 2);
    connect(&lw, SIGNAL(toRegister()), this, SLOT(switch_to_register())); //设定子窗口跳转关系
    connect(&rw, SIGNAL(toLogin()), this, SLOT(switch_to_login()));
    connect(&lw, SIGNAL(toMainWindow(QString)), this, SLOT(switch_to_MainWindow(QString))); //登录成功，切换至主窗口
}

Login_Register::~Login_Register() {
    delete ui;
}

void Login_Register::switch_to_login() { //切换至登录窗口
    setWindowTitle("登录");
    rw.hide();
    lw.refresh();
    lw.show();
}

void Login_Register::switch_to_register() { //切换至注册窗口
    setWindowTitle("注册");
    lw.hide();
    rw.refresh();
    rw.show();
}

void Login_Register::switch_to_MainWindow(QString usrname) { //切换至主窗口
    close();
    emit toMainWindow(usrname);
}
