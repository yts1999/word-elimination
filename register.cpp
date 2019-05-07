#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent, UserDatabase *_userdb) :
    QWidget(parent), ui(new Ui::Register), userdb(_userdb) {
    ui->setupUi(this);
    ui->userName->setValidator(new QRegExpValidator(QRegExp("^[A-Za-z0-9_]{0,20}$"), this));
}

Register::~Register() {
    delete ui;
}

void Register::refresh() {
    ui->userName->clear();
    ui->nickName->clear();
    ui->passWord->clear();
    ui->confirmpassWord->clear();
    ui->userCategory->setExclusive(false);
    ui->radioButton_player->setChecked(false);
    ui->radioButton_manager->setChecked(false);
    ui->userCategory->setExclusive(true);
}

void Register::on_loginButton_clicked() {
    emit toLogin();
}
