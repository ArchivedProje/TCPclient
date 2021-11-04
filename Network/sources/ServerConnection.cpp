// Copyright 2021 byteihq <kotov038@gmail.com>

#include <istream>
#include <ServerConnection.h>
#include <NetworkCommunication.h>
#include <nlohmann/json.hpp>
#include <utility>


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
