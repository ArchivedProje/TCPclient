// Copyright 2021 byteihq <kotov038@gmail.com>

#include <Server.h>

Server::Server(const std::shared_ptr<boost::asio::io_service> &ioService_) : acceptor_(*ioService_, tcp::endpoint(tcp::v4(), 2002)),
                                                            socket_(std::make_shared<tcp::socket>(*ioService_)), handler_(std::make_unique<Handler>()) {}

void Server::getMessage() {
    boost::system::error_code ec;
    boost::asio::read_until(*socket_, data_, '\n', ec);
    if (!ec) {
        std::istream ss(&data_);
        std::string sData;
        std::getline(ss, sData);
        sendMessage(handler_->request(sData));
    }
}

void Server::accept() {
    if (allSockets_.count(socket_) == 0) {
        acceptor_.accept(*socket_);
        allSockets_.insert(socket_);
    }
}

void Server::listen() {
    while (true) {
        getMessage();
    }
}

void Server::sendMessage(const nlohmann::json &msg) {
    boost::system::error_code ec;
    if (!msg.empty()) {
        boost::asio::write(*socket_, boost::asio::buffer(msg.dump() + '\n', msg.dump().size() + 1),
                           ec);
        if (!ec) {
            // log
        } else {
            // log
        }
    }
}
