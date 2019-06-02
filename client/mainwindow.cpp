#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player.h"
#include "manager.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QSqlRecord>
#include <QVariant>

MainWindow::MainWindow(QWidget *parent, Client *_client) :
    QMainWindow(parent), ui(new Ui::MainWindow), client(_client), addword(nullptr, _client), gw(nullptr, _client) {
    ui->setupUi(this);
    setFixedSize(800, 600); //设置窗口大小及位置
    move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 2);
    //player_model.setTable("user");
    //player_model.setFilter("type == 0");
    //player_model.removeColumn(1);
    //player_model.removeColumn(2);
    player_model.setColumnCount(5); //设置闯关者信息显示表格
    player_model.setHeaderData(0, Qt::Horizontal, "用户名");
    player_model.setHeaderData(1, Qt::Horizontal, "昵称");
    player_model.setHeaderData(2, Qt::Horizontal, "挑战关卡数");
    player_model.setHeaderData(3, Qt::Horizontal, "经验值");
    player_model.setHeaderData(4, Qt::Horizontal, "等级");
    //player_model.setSort(0, Qt::AscendingOrder);
    ui->player_table->setModel(&player_model);
    for (int i = 0; i < 5; i++) {
        ui->player_table->setColumnWidth(i, 120);
        ui->player_table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Fixed);
    }
    //manager_model.setTable("user");
    //manager_model.setFilter("type == 1");
    //manager_model.removeColumn(1);
    //manager_model.removeColumn(2);
    //manager_model.removeColumn(3);
    manager_model.setColumnCount(4); //设置出题者信息显示表格
    manager_model.setHeaderData(0, Qt::Horizontal, "用户名");
    manager_model.setHeaderData(1, Qt::Horizontal, "昵称");
    manager_model.setHeaderData(2, Qt::Horizontal, "出题数");
    manager_model.setHeaderData(3, Qt::Horizontal, "等级");
    //manager_model.setSort(0, Qt::AscendingOrder);
    ui->manager_table->setModel(&manager_model);
    for (int i = 0; i < 4; i++) {
        ui->manager_table->setColumnWidth(i, 150);
        ui->manager_table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Fixed);
    }
    addword.hide();
    gw.hide();
}

MainWindow::~MainWindow() {
    client->logout(user->get_name());
    delete ui;
}

void MainWindow::login_user(QString usrname) {
    Userdata usrinfo = client->get_usr_info(usrname); //获取用户信息
    if (usrinfo.usrtype == 0) { //如果用户为闯关者，删除出题者游戏选项
        user = new Player(usrinfo);
        ui->tabWidget->removeTab(1);
    }
    else { //如果用户为出题者，删除闯关者游戏选项
        user = new Manager(usrinfo);
        ui->tabWidget->removeTab(0);
    }
    connect(user, SIGNAL(modifyed()), this, SLOT(refresh_userinfo())); //用户信息被修改时刷新用户信息显示
    refresh_userinfo();
    show();
}

void MainWindow::refresh_userinfo() { //刷新用户信息显示
    Userdata usrinfo(user);
    client->update_usr_info(usrinfo); //更新数据库用户信息
    if (user->get_usrtype() == 0)
        ui->user_info->setText(QString("欢迎您，闯关者%1！挑战关卡数：%2　经验值：%3　等级：%4").arg(user->get_nickname()).arg(dynamic_cast<Player*>(user)->get_checknum()).arg(dynamic_cast<Player*>(user)->get_exp()).arg(user->get_level()));
     else
        ui->user_info->setText(QString("欢迎您，出题者%1！出题数：%2　等级：%3").arg(user->get_nickname()).arg(dynamic_cast<Manager*>(user)->get_probnum()).arg(user->get_level()));
}

void MainWindow::on_player_queryButton_clicked() { //闯关者数据查询
    QString cond;
    if (ui->player_select_checkBox->isChecked()) {
        int property = ui->player_select_property->currentIndex(); //获取设定的查询字符及内容
        QString field = ui->player_select_field->text();
        switch (property) { //根据查询字段及内容设定过滤器
        case 0:
            cond = QString("type == 0 and name == '%1'").arg(field);
            break;

        case 1:
            cond = QString("type == 0 and nickname == '%1'").arg(field);
            break;

        case 2:
            cond = QString("type == 0 and cp_num == '%1'").arg(field);
            break;

        case 3:
            cond = QString("type == 0 and exp == '%1'").arg(field);
            break;

        case 4:
            cond = QString("type == 0 and level == '%1'").arg(field);
        }
    }
    else
        cond = "type == 0";
    client->table_query(&player_model, 0, cond); //发送过滤器信息进行查询
    for (int i = 0; i < 5; i++) { //重新设置表格宽度
        ui->player_table->setColumnWidth(i, 120);
        ui->player_table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Fixed);
    }
}

void MainWindow::on_manager_queryButton_clicked() { //出题者数据查询
    QString cond;
    if (ui->manager_select_checkBox->isChecked()) {
        int property = ui->manager_select_property->currentIndex(); //获取设定的查询字段及内容
        QString field = ui->manager_select_field->text();
        switch (property) { //根据查询字段及内容设定过滤器
        case 0:
            cond = QString("type == 1 and name == '%1'").arg(field);
            break;

        case 1:
            cond = QString("type == 1 and nickname == '%1'").arg(field);
            break;

        case 2:
            cond = QString("type == 1 and cp_num == '%1'").arg(field);
            break;

        case 3:
            cond = QString("type == 1 and level == '%1'").arg(field);

        }
    }
    else
        cond = "type == 1";
    client->table_query(&manager_model, 1, cond);
    for (int i = 0; i < 4; i++) {
        ui->manager_table->setColumnWidth(i, 150);
        ui->manager_table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Fixed);
    }
}

void MainWindow::on_player_select_checkBox_stateChanged(int arg1) { //根据闯关者查询勾选情况启用或禁用查找选项
    switch (arg1) {
    case (Qt::Unchecked):
        ui->player_select_property->setEnabled(false);
        ui->player_select_field->setEnabled(false);
        break;

    case (Qt::Checked):
        ui->player_select_property->setEnabled(true);
        ui->player_select_field->setEnabled(true);

    }
}

void MainWindow::on_manager_select_checkBox_stateChanged(int arg1) { //根据出题者查询勾选情况启用或禁用查找选项
    switch (arg1) {
    case (Qt::Unchecked):
        ui->manager_select_property->setEnabled(false);
        ui->manager_select_field->setEnabled(false);
        break;

    case (Qt::Checked):
        ui->manager_select_property->setEnabled(true);
        ui->manager_select_field->setEnabled(true);

    }
}

void MainWindow::on_addwordButton_clicked() { //添加单词
    addword.set_manager(dynamic_cast<Manager*>(user));
    addword.show();
}

void MainWindow::on_gameButton_clicked() { //开始游戏
    gw.init(dynamic_cast<Player*>(user));
    gw.show();
}
