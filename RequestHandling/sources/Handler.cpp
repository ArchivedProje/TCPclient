// Copyright 2021 byteihq <kotov038@gmail.com>

#include <Handler.h>
#include <NetworkCommunication.h>


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
    }
    return reply;
}

nlohmann::json Handler::reply(const std::string& sender, const std::string &reply) {
    nlohmann::json request = {
            {"sender", sender},
            {"type", Requests::Msg},
            {"data", reply}
    };
    return request;
}
