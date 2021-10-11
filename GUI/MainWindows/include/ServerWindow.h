// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_SERVERWINDOW_H
#define TCPCLIENT_SERVERWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <memory>
#include <Connection.h>

class ServerWindow : public QWidget {
private:
    std::unique_ptr<QGridLayout> gridLayout_;
    std::unique_ptr<QListWidget> infoWidget_;
    std::unique_ptr<QLineEdit> lineEdit_;
    std::unique_ptr<QPushButton> sendBtn_;
    std::unique_ptr<QPushButton> usersBtn_;
    std::unique_ptr<QPushButton> exitBtn_;
public:
    explicit ServerWindow(QWidget *parent);
};

#endif //TCPCLIENT_SERVERWINDOW_H
