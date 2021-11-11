// Copyright 2021 byteihq <kotov038@gmail.com>

#include <istream>
#include <Connection.h>
#include <boost/lambda/lambda.hpp>
#include <boost/bind/bind.hpp>
#include <nlohmann/json.hpp>

Connection::Connection() : ioService_(std::make_shared<boost::asio::io_service>()), socket_(std::make_shared<tcp::socket>(*ioService_)), deadline_(*ioService_), handler_(std::make_unique<Handler>()), delim_("MSGEND") {
    deadline_.expires_at(boost::posix_time::pos_infin);
    checkDeadline();
}

int Connection::AsyncConnect(const std::string &ip_, int port_) {
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
    socket_->async_connect(tcp::endpoint(ip, port_), boost::lambda::var(ec) = boost::lambda::_1);
    do ioService_->run_one(); while (ec == boost::asio::error::would_block);
    if (ec || !socket_->is_open()) {
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
    if (msg.empty()) {
        return;
    }
    boost::asio::write(*socket_, boost::asio::buffer(msg.dump() + delim_, msg.dump().size() + delim_.size()),
                       ec);
    if (!ec) {
        // log
    } else {
        // log
    }
}

void Connection::getMessage() {
    boost::system::error_code ec;
    boost::asio::read_until(*socket_, data_, delim_, ec);
    if (!ec) {
        std::istream ss(&data_);
        std::string sData(std::istreambuf_iterator<char>(ss), {});
        sData.erase(sData.end() - delim_.size(), sData.end());
        handler_->request(sData);
    }
}

void Connection::listen() {
    while (true) {
        // other logic

        getMessage();
    }
}

int Connection::Connect(const std::string &ip_, int port_) {
    boost::system::error_code ec;
    auto ip = boost::asio::ip::address::from_string(ip_, ec);
    if (ec) {
        return -1;
    }
    socket_->connect(tcp::endpoint(ip, port_));
    return 0;
}

void Connection::sendFileData(const char *data, size_t size) {
    boost::system::error_code ec;
    std::string strData(data, size);
    boost::asio::write(*socket_,
                       boost::asio::buffer(strData + delim_, strData.size() + delim_.size()),
                       ec);
    if (!ec) {
        // log
    } else {
        // log
    }
}

std::pair<boost::array<char, 1000>, size_t> Connection::readSome() {
    auto bytes = boost::asio::read(*socket_, boost::asio::buffer(buffer_.data(), buffer_.size()));
    return {buffer_, bytes};
}
