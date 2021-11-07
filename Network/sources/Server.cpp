// Copyright 2021 byteihq <kotov038@gmail.com>

#include <Server.h>

Server::Server(std::shared_ptr<boost::asio::io_service> &ioService) : acceptor_(
        std::make_shared<tcp::acceptor>(*ioService, tcp::endpoint(tcp::v4(), 2002))),
                                                                      socket_(std::make_shared<tcp::socket>(
                                                                              *ioService)),
                                                                      handler_(std::make_unique<Handler>()) {}

void Server::getMessage() {
    boost::system::error_code ec;
    boost::asio::read_until(*socket_, data_, "msg_end", ec);
    if (!ec) {
        std::istream ss(&data_);
        std::string sData;
        std::string line;
        bool first = true;
        while (std::getline(ss, line)) {
            if (!first) {
                sData += '\n';
            }
            first = false;
            sData += line;
        }
        handler_->request(sData);
    }
}

void Server::accept() {
    acceptor_->accept(*socket_);

}

void Server::listen() {
    while (true) {
        getMessage();
    }
}

void Server::sendMessage(const nlohmann::json &msg) {
    boost::system::error_code ec;
    if (msg.empty()) {
        return;
    }
    boost::asio::write(*socket_, boost::asio::buffer(msg.dump() + "msg_end", msg.dump().size() + 7),
                       ec);
    if (!ec) {
        // log
    } else {
        // log
    }

}

void Server::reload(std::shared_ptr<boost::asio::io_service> &ioService) {
    acceptor_->close();
    acceptor_.reset(new tcp::acceptor(*ioService, tcp::endpoint(tcp::v4(), 2002)));
    socket_->close();
    socket_.reset(new tcp::socket(*ioService));
}

void Server::sendFileData(const nlohmann::json &msg, char *data, size_t size) {
    boost::system::error_code ec;
    if (msg.empty()) {
        return;
    }
    std::string strData(data, size);
    boost::asio::write(*socket_,
                       boost::asio::buffer(msg.dump() + " || " + strData + "msg_end", msg.dump().size() + 11 + size),
                       ec);
    if (!ec) {
        // log
    } else {
        // log
    }
}
