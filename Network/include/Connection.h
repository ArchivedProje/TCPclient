// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_CONNECTION_H
#define TCPCLIENT_CONNECTION_H

#include <boost/asio.hpp>
#include <string>

using boost::asio::ip::tcp;

class Connection {
private:
    tcp::socket socket_;
public:
    explicit Connection(boost::asio::io_service &io_service);
    int connect(const std::string& ip_, int port_);
};

#endif //TCPCLIENT_CONNECTION_H
