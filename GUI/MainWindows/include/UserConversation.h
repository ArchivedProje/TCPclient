// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_USERCONVERSATION_H
#define TCPCLIENT_USERCONVERSATION_H

#include <QWidget>
#include <memory>
#include <string>
#include <QThread>
#include <QString>
#include <Resizable.h>
#include <StyleSettings.h>
#include <ClientConnection.h>
#include <Server.h>
#include <QGridLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QProgressBar>
#include <QPoint>

class MainWindow;

class UserConversation : public Resizable {
private:
    friend class MainWindow;
    std::unique_ptr<ClientConnection> clientConnection_;
    std::unique_ptr<Server> serverConnection_;
    std::shared_ptr<QThread> clientThread_;
    std::shared_ptr<QThread> serverThread_;
    using upPB = std::unique_ptr<QPushButton>;
    using upQL = std::unique_ptr<QListWidget>;
    std::unique_ptr<QGridLayout> qgrid_;
    upQL leftList_;
    upQL rightList_;
    std::unique_ptr<QProgressBar> progress_;
    std::unique_ptr<QLineEdit> lineEdit_;
    upPB sendBtn_;
    upPB disconnectBtn_;
    std::string sender_;
    size_t msgNumber_;

    enum ConnectionMode {
        ServerMode,
        ClientMode,
    };

    ConnectionMode connectionMode_;

    void setSender(const std::string& sender);

private slots:

    void startServer();

    void startClient(const QString& ip);

    void setDarkMode();

    void setLightMode();

    void sendBtnClicked();

    void showNewMsg(const QString& sender, const QString& msg);

    void ShowContextMenu(const QPoint& point);

    void actionReply();

    void actionCopy();

    void disconnectBtnClicked();

public:
    explicit UserConversation(QWidget *parent, std::shared_ptr<QThread> clientThread,
                              std::shared_ptr<QThread> serverThread, const std::shared_ptr<boost::asio::io_service>& ioService_, Mode mode);
};

#endif //TCPCLIENT_USERCONVERSATION_H
