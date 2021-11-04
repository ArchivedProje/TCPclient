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
        std::cerr << sData << std::endl;
    }
}

void Server::accept() {
    std::cerr << "Accepting";
    acceptor_.accept(socket_);
    std::cerr << "Accepted";
}

void Server::listen() {
    while (true) {
        getMessage();
    }
}

void Server::sendMessage(const nlohmann::json &msg) {
    boost::system::error_code ec;
    if (!msg.empty()) {
        boost::asio::write(socket_, boost::asio::buffer(msg.dump() + '\n', msg.dump().size() + 1),
                           ec);
        if (!ec) {
            // log
        } else {
            // log
        }
    }
}
