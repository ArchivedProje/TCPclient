// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_SERVER_H
#define TCPCLIENT_SERVER_H

#include <boost/asio.hpp>
#include <memory>
#include <QObject>
#include <nlohmann/json.hpp>
#include <Handler.h>

using boost::asio::ip::tcp;

class Server : public QObject {
    Q_OBJECT
private:
    tcp::acceptor acceptor_;
    tcp::socket socket_;
    boost::asio::streambuf data_;
    void getMessage();
public:
    std::unique_ptr<Handler> handler_;

    explicit Server(const std::shared_ptr<boost::asio::io_service>& ioService);

    void accept();

    void sendMessage(const nlohmann::json &msg);

    void closeConnection();
public slots:

    void listen();
};

#endif //TCPCLIENT_SERVER_H
