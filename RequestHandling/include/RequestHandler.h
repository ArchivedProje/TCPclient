//Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_REQUESTHANDLER_H
#define TCPCLIENT_REQUESTHANDLER_H

#include <string>
#include <nlohmann/json.hpp>
#include <QObject>

class RequestHandler : public QObject {
    Q_OBJECT
signals:
    void authorizeFailed();

    void authorizeSucceed();

    void unknownStatus();

public:
    RequestHandler() = default;

    nlohmann::json handle(const std::string& request);
};

#endif //TCPCLIENT_REQUESTHANDLER_H
