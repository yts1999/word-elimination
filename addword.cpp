#include "addword.h"
#include "ui_addword.h"
#include <QDesktopWidget>
#include <QRegExpValidator>
#include <QMessageBox>

Addword::Addword(QWidget *parent, WordDatabase *_worddb) :
    QDialog(parent), ui(new Ui::Addword), worddb(_worddb), manager(nullptr) {
    ui->setupUi(this);
    setFixedSize(500, 400);
    move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 2);
    ui->wordInput->setValidator(new QRegExpValidator(QRegExp("^[a-z]{1,100}$"), this));
}

Addword::~Addword() {
    delete ui;
}

void Addword::set_manager(Manager *_manager) {
    manager = _manager;
}

void Addword::on_addwordButton_clicked() {
    QString word_input = ui->wordInput->text();
    if (word_input == "")
        QMessageBox::warning(this, "提示", "请输入单词！");
    else {
        worddb->add_word(word_input);
        manager->inc_probnum();
        QMessageBox::information(this, "成功", "添加成功！");
        ui->wordInput->clear();
    }
}

void Addword::on_returnButton_clicked() {
    ui->wordInput->clear();
    hide();
}
