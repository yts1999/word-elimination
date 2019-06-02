#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QMessageBox>

Gamewindow::Gamewindow(QWidget *parent, Client *_client) :
    QDialog(parent), ui(new Ui::Gamewindow), player(nullptr), show_timer_value(0), wait_timer_value(0), word_counter(0), word_counter_limit(0), client(_client), tim(0, 0, 0) {
    ui->setupUi(this);
    show_timer.setSingleShot(true);
    wait_timer.setSingleShot(true);
    connect(&show_timer, SIGNAL(timeout()), this, SLOT(progress_switch())); //显示定时器超时时切换进度条状态
    connect(&wait_timer, SIGNAL(timeout()), this, SLOT(word_switch())); //等待定时器超时时切换单词
    connect(ui->wordInput, SIGNAL(returnPressed()), this, SLOT(word_switch())); //按下回车时切换单词
}

Gamewindow::~Gamewindow() {
    delete ui;
}

void Gamewindow::init(Player *_player) { //用户信息及界面初始化
    player = _player;
    int level = player->get_checknum() + 1;
    ui->level->setText(QString("第%1关").arg(level));
    word_counter = 0; //清空单词计数器
    word_counter_limit = (level - 1) / 3 + 1; //设置单词数量、显示时间及输入时间
    if (level < 10)
        show_timer_value = 5;
    else
        if (level < 15)
            show_timer_value = 4;
        else
            if (level < 20)
                show_timer_value = 3;
            else
                if (level < 25)
                    show_timer_value = 2;
                else
                    show_timer_value = 1;
    if (level < 10)
        wait_timer_value = 7;
    else
        if (level < 15)
            wait_timer_value = 5;
        else
            if (level < 20)
                wait_timer_value = 3;
            else
                if (level < 25)
                    wait_timer_value = 2;
                else
                    wait_timer_value = 1;
    tim.start();
    game_begin();
}

void Gamewindow::on_pushButton_clicked() {
    show_timer.stop(); //关闭定时器窗口
    wait_timer.stop();
    hide();
}

void Gamewindow::progress_switch() {
    show_timer.stop();
    int val = ui->progressBar->value() - 100 / show_timer_value; //更新进度条
    if (val < show_timer_value)
        val = 0;
    ui->progressBar->setValue(val);
    if (val == 0) { //进度条读完，进入输入阶段
        ui->word_show->hide();
        ui->wordInput->setEnabled(true);
        ui->wordInput->setFocus();
        wait_timer.start(wait_timer_value * 1000);
    }
    else
        show_timer.start(1000); //设定1s的定时器
}

void Gamewindow::word_switch() {
    wait_timer.stop();
    if (ui->wordInput->text() != ui->word_show->text()) { //单词不匹配
        QMessageBox::critical(this, "失败", "闯关失败！");
        hide();
        return;
    }
    word_counter++; //单词匹配，单词计数器加1
    if (word_counter == word_counter_limit) { //本轮单词输入已经结束
        QMessageBox::information(this, "成功", "闯关成功！");
        int tim_elapsed = tim.elapsed();
        player->inc_checknum(); //过关数增加
        player->add_exp(10 * player->get_checknum() - tim_elapsed / 1000 <= 10 ? 10 : 10 * player->get_checknum() - tim_elapsed / 1000);
        hide();
        return;
    }
    game_begin();
}

void Gamewindow::game_begin() { //显示新的单词
    ui->wordInput->clear();
    ui->wordInput->setEnabled(false);
    ui->word_show->setText(client->get_word(player->get_checknum() + 1)); //根据关卡号从数据库获取一个单词
    if (ui->word_show->text() == "") {
        QMessageBox::critical(this, "错误", "找不到单词！");
        show_timer.stop();
        wait_timer.stop();
        hide();
    }
    ui->word_show->show();
    ui->progressBar->setValue(100);
    show_timer.start(1000);
}
