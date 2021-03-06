// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_SERVERWINDOW_H
#define TCPCLIENT_SERVERWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QPoint>
#include <QMap>
#include <QString>
#include <memory>
#include <string>
#include <ServerConnection.h>
#include <Resizable.h>
#include <NetworkCommunication.h>
#include <UsersWindow.h>

class MainWindow;

class ServerWindow : public Resizable {
Q_OBJECT
private:
    friend class MainWindow;

    using upPB = std::unique_ptr<QPushButton>;
    std::shared_ptr<ServerConnection> connection_;
    std::unique_ptr<QGridLayout> gridLayout_;
    std::unique_ptr<QListWidget> infoWidget_;
    std::unique_ptr<QLineEdit> lineEdit_;
    upPB sendBtn_;

    std::string sender_;
    size_t msgNumber_;

    void setSender(const std::string& sender);

private slots:

    void sendBtnClicked();

    void ShowContextMenu(const QPoint& point);

    void actionReply();

    void actionCopy();

    void actionDisconnect();

    void showNewMsg(const QString& sender, const QString& msg, const QString& status);

    void actionGetUsers();

signals:

    void closeWindow();

public:
    explicit ServerWindow(std::shared_ptr<ServerConnection> connection, QWidget *parent);
};

#endif //TCPCLIENT_SERVERWINDOW_H
