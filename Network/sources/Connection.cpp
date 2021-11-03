// Copyright 2021 byteihq <kotov038@gmail.com>

#include <istream>
#include <Connection.h>
#include <NetworkCommunication.h>
#include <boost/lambda/lambda.hpp>
#include <boost/bind/bind.hpp>
#include <nlohmann/json.hpp>

Connection::Connection() : socket_(ioService_), deadline_(ioService_), handler_(std::make_unique<Handler>()) {
    deadline_.expires_at(boost::posix_time::pos_infin);
    checkDeadline();
}

int Connection::Connect(const std::string &ip_, int port_) {
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
    ec = boost::asio::error::would_block;
    deadline_.expires_from_now(boost::posix_time::seconds(2));
    socket_.async_connect(tcp::endpoint(ip, port_), boost::lambda::var(ec) = boost::lambda::_1);
    do ioService_.run_one(); while (ec == boost::asio::error::would_block);
    if (ec || !socket_.is_open()) {
        return -2;
    }
    return 0;
}

void Connection::checkDeadline() {
    if (deadline_.expires_at() <= boost::asio::deadline_timer::traits_type::now()) {
        deadline_.expires_at(boost::posix_time::pos_infin);
    }
    deadline_.async_wait(boost::bind(&Connection::checkDeadline, this));
}

void Connection::sendMessage(const nlohmann::json &msg) {
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

void Connection::getMessage() {
    boost::system::error_code ec;
    boost::asio::read_until(socket_, data_, '\n', ec);
    if (!ec) {
        std::istream ss(&data_);
        std::string sData;
        std::getline(ss, sData);
        sendMessage(handler_->request(sData).dump());
    }
}

void Connection::listen() {
    while (true) {
        // other logic

        getMessage();
    }
}
