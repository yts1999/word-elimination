#include "addword.h"
#include "ui_addword.h"
#include <QDesktopWidget>
#include <QRegExpValidator>
#include <QMessageBox>

Addword::Addword(QWidget *parent, Client *_client) :
    QDialog(parent), ui(new Ui::Addword), client(_client), manager(nullptr) { // 设定窗口大小位置
    ui->setupUi(this);
    setFixedSize(500, 400);
    move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 2);
    ui->wordInput->setValidator(new QRegExpValidator(QRegExp("^[a-z]{1,100}$"), this)); //通过正则表达式限制输入
}

Addword::~Addword() {
    delete ui;
}

void Addword::set_manager(Manager *_manager) { //设置出题者信息
    manager = _manager;
}

void Addword::on_addwordButton_clicked() {
    QString word_input = ui->wordInput->text(); //接受单词输入
    if (word_input == "") //输入为空
        QMessageBox::warning(this, "提示", "请输入单词！");
    else
        if (! client->add_word(word_input)) //单词已经存在
            QMessageBox::warning(this, "提示", "该单词已存在！");
        else { //输入合法
            manager->inc_probnum(); //增加出题者出题数
            QMessageBox::information(this, "成功", "添加成功！");
            ui->wordInput->clear();
        }
}

void Addword::on_returnButton_clicked() {
    ui->wordInput->clear();
    hide();
}
