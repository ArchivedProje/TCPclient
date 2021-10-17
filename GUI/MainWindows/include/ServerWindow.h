// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_SERVERWINDOW_H
#define TCPCLIENT_SERVERWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <memory>
#include <string>
#include <Connection.h>
#include <Resizable.h>

class MainWindow;

class ServerWindow : public Resizable {
Q_OBJECT
private:
    friend class MainWindow;

    using upPB = std::unique_ptr<QPushButton>;
    std::shared_ptr<Connection> connection_;
    std::unique_ptr<QGridLayout> gridLayout_;
    std::unique_ptr<QListWidget> infoWidget_;
    std::unique_ptr<QLineEdit> lineEdit_;
    upPB sendBtn_;

    std::string sender_;

    void setSender(const std::string& sender);

private slots:

    void sendBtnClicked();

signals:

    void closeWindow();

public:
    explicit ServerWindow(std::shared_ptr<Connection> connection, QWidget *parent);
};

#endif //TCPCLIENT_SERVERWINDOW_H
