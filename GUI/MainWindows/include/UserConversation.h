// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_USERCONVERSATION_H
#define TCPCLIENT_USERCONVERSATION_H

#include <QWidget>
#include <memory>
#include <QThread>
#include <QString>
#include <Resizable.h>
#include <StyleSettings.h>
#include <ClientConnection.h>
#include <Server.h>

class MainWindow;

class UserConversation : public Resizable {
private:
    friend class MainWindow;
    std::unique_ptr<ClientConnection> clientConnection_;
    std::unique_ptr<Server> serverConnection_;
    std::shared_ptr<QThread> clientThread_;
    std::shared_ptr<QThread> serverThread_;
private slots:

    void startServer();

    void startClient(const QString& ip);

public:
    explicit UserConversation(QWidget *parent, std::shared_ptr<QThread> clientThread,
                              std::shared_ptr<QThread> serverThread, const std::shared_ptr<boost::asio::io_service>& ioService_, Mode mode);
};

#endif //TCPCLIENT_USERCONVERSATION_H
