// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_CONNECTION_H
#define TCPCLIENT_CONNECTION_H

#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <string>
#include <memory>
#include <nlohmann/json.hpp>
#include <Handler.h>
#include <QObject>
using boost::asio::ip::tcp;


class Connection : public QObject {
    Q_OBJECT
protected:
    boost::asio::io_service ioService_;
    std::shared_ptr<tcp::socket> socket_;
    boost::asio::deadline_timer deadline_;
    boost::asio::streambuf data_;
    void checkDeadline();

    void getMessage();

public:

    std::unique_ptr<Handler> handler_;
    
    Connection();

    int AsyncConnect(const std::string &ip_, int port_);

    int Connect(const std::string &ip_, int port_);

    void sendMessage(const nlohmann::json &msg);

public slots:

    void listen();
};

#endif //TCPCLIENT_CONNECTION_H
