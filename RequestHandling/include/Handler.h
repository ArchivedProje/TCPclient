//Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_HANDLER_H
#define TCPCLIENT_HANDLER_H

#include <string>
#include <nlohmann/json.hpp>
#include <QObject>

class Handler : public QObject {
Q_OBJECT
signals:

    void authorizeFailed();

    void authorizeSucceed();

    void unknownStatus();

public:
    Handler() = default;

    nlohmann::json request(const std::string &request);

    nlohmann::json reply(const std::string& sender, const std::string &reply);
};

#endif //TCPCLIENT_HANDLER_H
