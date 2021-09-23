// Copyright 2021 byteihq <kotov038@gmail.com>

#include <Connection.h>

Connection::Connection(boost::asio::io_service &io_service) : socket_(io_service) {}

int Connection::connect(const std::string &ip_, int port_) {
    /*
     * -2 - server not responding / the computer isn't connected to the Internet
     * -1 - wrong ip
     * 0 - everything is fine
     */
    boost::system::error_code ec;
    auto ip = boost::asio::ip::address::from_string(ip_, ec);
    if (ec) {
        return -1;
    }
        socket_.connect(tcp::endpoint(ip, port_), ec);
    if (ec) {
        return -2;
    }
    return 0;
}
