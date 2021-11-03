//

#include <Server.h>
#include <iostream>

Server::Server(const std::shared_ptr<boost::asio::io_service> &ioService_) : acceptor_(*ioService_, tcp::endpoint(tcp::v4(), 2002)),
                                                            socket_(*ioService_) {}

void Server::getMessage() {
    boost::system::error_code ec;
    boost::asio::read_until(socket_, data_, '\n', ec);
    if (!ec) {
        std::istream ss(&data_);
        std::string sData;
        std::getline(ss, sData);
        std::cerr << sData;
    }
}

void Server::accept() {
    acceptor_.accept(socket_);
}
