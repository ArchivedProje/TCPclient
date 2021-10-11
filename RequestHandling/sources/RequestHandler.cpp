// Copyright 2021 byteihq <kotov038@gmail.com>

#include <RequestHandler.h>
#include <NetworkCommunication.h>


nlohmann::json RequestHandler::handle(const std::string &request) {
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
