// Copyright 2021 byteihq <kotov038@gmail.com>

#include <Handler.h>

nlohmann::json Handler::request(const std::string &request) {
    nlohmann::json jsonRequest = nlohmann::json::parse(request);
    nlohmann::json reply;
    if (jsonRequest["type"] == Requests::Auth) {
        if (jsonRequest["data"] == Replies::Auth::Successful) {
            emit authorizeSucceed();
        } else if (jsonRequest["data"] == Replies::Auth::Unsuccessful) {
            emit authorizeFailed();
        } else {
            emit unknownStatus();
        }
    } else if (jsonRequest["type"] == Requests::Msg) {
        emit newMsg(QString::fromStdString(jsonRequest["sender"].get<std::string>()), QString::fromStdString(jsonRequest["data"].get<std::string>()));
    }
    return reply;
}

nlohmann::json Handler::reply(const std::string& sender, const std::string &reply, Requests requestType) {
    nlohmann::json request = {
            {"sender", sender},
            {"type", requestType},
            {"data", reply}
    };
    return request;
}
