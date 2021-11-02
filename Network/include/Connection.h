//
// Created by byteihq on 02.11.2021.
//

#ifndef TCPCLIENT_CONNECTION_H
#define TCPCLIENT_CONNECTION_H

#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <string>
#include <memory>
#include <nlohmann/json.hpp>
#include <Handler.h>

using boost::asio::ip::tcp;

class Connection {
protected:
    boost::asio::io_service ioService_;
    tcp::socket socket_;
    boost::asio::deadline_timer deadline_;
    boost::asio::streambuf data_;

    void checkDeadline();

public:
    Connection();

    int Connect(const std::string &ip_, int port_);

    void sendMessage(const nlohmann::json &msg);

};

#endif //TCPCLIENT_CONNECTION_H
