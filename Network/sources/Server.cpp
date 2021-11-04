// Copyright 2021 byteihq <kotov038@gmail.com>

#include <Server.h>

Server::Server(const std::shared_ptr<boost::asio::io_service> &ioService_) : acceptor_(*ioService_, tcp::endpoint(tcp::v4(), 2002)),
                                                            socket_(*ioService_), handler_(std::make_unique<Handler>()) {}

void Server::getMessage() {
    boost::system::error_code ec;
    boost::asio::read_until(socket_, data_, '\n', ec);
    if (!ec) {
        std::istream ss(&data_);
        std::string sData;
        std::getline(ss, sData);
        sendMessage(handler_->request(sData));
    }
}

void Server::accept() {
    acceptor_.accept(socket_);
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

void Server::closeConnection() {
    acceptor_.close();
    socket_.close();
}
