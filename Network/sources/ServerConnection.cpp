// Copyright 2021 byteihq <kotov038@gmail.com>

#include <istream>
#include <ServerConnection.h>
#include <NetworkCommunication.h>
#include <boost/bind/bind.hpp>
#include <nlohmann/json.hpp>

ServerConnection::ServerConnection() : handler_(std::make_unique<Handler>()) {}

int ServerConnection::authorize(const std::string &login, const std::string &password) {
    boost::system::error_code ec;
    nlohmann::json msg = {
            {"sender", login},
            {"type",   Requests::Auth},
            {"data",   {{"login", login}, {"password", password}}}
    };
    sendMessage(msg);

    /*
     * -1 - error
     * 0 - message sent
     */
    return ec ? -1 : 0;
}

void ServerConnection::listen() {
    while (true) {
        // other logic

        getMessage();
    }
}

void ServerConnection::getMessage() {
    boost::system::error_code ec;
    boost::asio::read_until(socket_, data_, '\n', ec);
    if (!ec) {
        std::istream ss(&data_);
        std::string sData;
        std::getline(ss, sData);
        sendMessage(handler_->request(sData).dump());
    }
}
