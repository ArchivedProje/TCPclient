// Copyright 2021 byteihq <kotov038@gmail.com>

#include <UserConversation.h>
#include <QMessageBox>
#include <iostream>

UserConversation::UserConversation(QWidget *parent, std::shared_ptr<QThread> clientThread,
                                   std::shared_ptr<QThread> serverThread,
                                   const std::shared_ptr<boost::asio::io_service> &ioService_, Mode mode) : Resizable(
        parent, 100, 100),
                                                                                                            clientConnection_(
                                                                                                                    std::make_unique<ClientConnection>()),
                                                                                                            serverConnection_(
                                                                                                                    std::make_unique<Server>(ioService_)),
                                                                                                            clientThread_(
                                                                                                                    std::move(
                                                                                                                            clientThread)),
                                                                                                            serverThread_(
                                                                                                                    std::move(
                                                                                                                            serverThread)) {

    if (mode == Mode::Dark) {
        StyleSettings::setDarkMode(this);
    } else {
        StyleSettings::setLightMode(this);
    }

}

void UserConversation::startClient(const QString &ip) {
    clientConnection_->moveToThread(clientThread_.get());
    clientThread_->start();
//    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cerr << ip.toStdString();
    auto status = clientConnection_->Connect(ip.toStdString(), 2002);
    if (status == -2) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Server not responding");
        msgBox.exec();
        return;
    }
    if (status == -1) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Ip is wrong");
        msgBox.exec();
        return;
    }
    nlohmann::json msg = {
            {"sender", "user1"}
    };
    clientConnection_->sendMessage(msg.dump());
    clientConnection_->listen();
}

void UserConversation::startServer() {
    serverConnection_->moveToThread(serverThread_.get());
    serverThread_->start();
    serverConnection_->accept();
    serverConnection_->listen();
}
