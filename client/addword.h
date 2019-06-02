#ifndef ADDWORD_H
#define ADDWORD_H

#include "client.h"
#include "manager.h"
#include <QDialog>

namespace Ui {
class Addword;
}

class Addword : public QDialog {
    Q_OBJECT

public:
    explicit Addword(QWidget *parent = nullptr, Client *_client = nullptr);
    ~Addword();
    void set_manager(Manager *_manager);

private slots:
    void on_addwordButton_clicked();
    void on_returnButton_clicked();

private:
    Ui::Addword *ui;
    Client *client;
    Manager *manager;
};

#endif // ADDWORD_H
