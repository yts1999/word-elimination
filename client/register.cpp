#include "register.h"
#include "ui_register.h"
#include <QMessageBox>
#include <QRegExpValidator>

Register::Register(QWidget *parent, Client *_client) :
    QWidget(parent), ui(new Ui::Register), client(_client) {
    ui->setupUi(this);
    //使用正则表达式限定输入格式
    ui->userName->setValidator(new QRegExpValidator(QRegExp("^[A-Za-z0-9_]{0,10}$"), this));
    ui->nickName->setValidator(new QRegExpValidator(QRegExp("^.{0,20}$"), this));
    ui->passWord->setValidator(new QRegExpValidator(QRegExp("^.{0,20}$"), this));
    ui->confirmpassWord->setValidator(new QRegExpValidator(QRegExp("^.{0,20}$"), this));
}

Register::~Register() {
    delete ui;
}

void Register::refresh() { //清空所有输入
    ui->userName->clear();
    ui->nickName->clear();
    ui->passWord->clear();
    ui->confirmpassWord->clear();
    ui->userCategory->setExclusive(false);
    ui->radioButton_player->setChecked(false);
    ui->radioButton_manager->setChecked(false);
    ui->userCategory->setExclusive(true);
}

void Register::on_confirmButton_clicked() {
    QString usr = ui->userName->text(), name = ui->nickName->text(), pwd = ui->passWord->text(), cpwd = ui->confirmpassWord->text(); //获取表单信息
    int usrtype = ui->userCategory->checkedId();
    if (usr == "")
        QMessageBox::warning(this, "提示", "请输入用户名！");
    else
        if (name == "")
            QMessageBox::warning(this, "提示", "请输入昵称！");
        else
            if (pwd == "")
                QMessageBox::warning(this, "提示", "请输入密码！");
            else
                if (cpwd == "")
                    QMessageBox::warning(this, "提示", "请再次输入密码以确认！");
                else
                    if (pwd != cpwd)
                        QMessageBox::warning(this, "提示", "两次密码输入不符！");
                    else
                        if (usrtype == -1)
                            QMessageBox::warning(this, "提示", "请选择用户类型！");
                        else
                            if (! client->add_usr(usr, pwd, name, usrtype))
                                QMessageBox::warning(this, "提示", "该用户名已存在！");
                            else {
                                QMessageBox::information(this, "成功", "注册成功！");
                                refresh();
                            }
}

void Register::on_loginButton_clicked() {
    emit toLogin();
}
