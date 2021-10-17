//Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_HANDLER_H
#define TCPCLIENT_HANDLER_H

#include <string>
#include <QObject>
#include <nlohmann/json.hpp>
#include <NetworkCommunication.h>

class Handler : public QObject {
Q_OBJECT
signals:

    void authorizeFailed();

    void authorizeSucceed();

    void unknownStatus();

public:
    Handler() = default;

    nlohmann::json request(const std::string &request);

    nlohmann::json reply(const std::string& sender, const std::string &reply, Requests requestType);
};

#endif //TCPCLIENT_HANDLER_H
