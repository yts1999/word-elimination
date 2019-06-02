#ifndef REGISTER_H
#define REGISTER_H

#include "client.h"
#include <QWidget>

namespace Ui {
    class Register;
}

class Register : public QWidget {
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr, Client *_client = nullptr);
    ~Register();
    void refresh();

signals:
    void toLogin();

private slots:
    void on_confirmButton_clicked();
    void on_loginButton_clicked();

private:
    Ui::Register *ui;
    Client *client;
};

#endif // REGISTER_H
