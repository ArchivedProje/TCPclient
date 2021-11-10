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
#include <nlohmann/json.hpp>

class MainWindow;

class UserConversation : public Resizable {
private:
    friend class MainWindow;
    std::shared_ptr<boost::asio::io_service>& ioService_;
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

    void sendMsg(const nlohmann::json& msg);

private slots:

    void startServer();

    void startClient(const QString& ip);

    void setDarkMode();

    void setLightMode();

    void sendBtnClicked();

    void showNewMsg(const QString& sender, const QString& msg);

    void showRightContextMenu(const QPoint& point);

    void showLeftContextMenu(const QPoint& point);

    void actionGet();

    void actionReply();

    void actionCopy();

    void sendAllFiles();

    void sendFile(const QString& path);

    void noFile(const QString& path);

    void setAllFiles(const Handler::StringList& paths);

    void setFile(const QString &name, const Handler::Array& data, int maxSize, Handler::StreamSize gcount);

    void sendFileData(const char* data, size_t size);

    void disconnectBtnClicked();

public:
    explicit UserConversation(QWidget *parent, std::shared_ptr<QThread> clientThread,
                              std::shared_ptr<QThread> serverThread, std::shared_ptr<boost::asio::io_service>& ioService, Mode mode);
};

#endif //TCPCLIENT_USERCONVERSATION_H
