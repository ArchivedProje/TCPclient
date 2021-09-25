// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_CONNECTION_H
#define TCPCLIENT_CONNECTION_H

#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <string>

using boost::asio::ip::tcp;

class Connection {
private:
    boost::asio::io_service ioService_;
    tcp::socket socket_;
    boost::asio::deadline_timer deadline_;
    void checkDeadline();
public:
    Connection();
    int connect(const std::string& ip_, int port_);
    int authorize(const std::string& login, const std::string& password);
    void sendMessage();
};

#endif //TCPCLIENT_CONNECTION_H
