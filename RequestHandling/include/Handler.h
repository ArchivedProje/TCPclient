//Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_HANDLER_H
#define TCPCLIENT_HANDLER_H

#include <string>
#include <QObject>
#include <map>
#include <QString>
#include <nlohmann/json.hpp>
#include <NetworkCommunication.h>

class Handler : public QObject {
Q_OBJECT
public:
    typedef std::map<std::string, std::string> StringMap;
signals:

    void authorizeFailed();

    void authorizeSucceed();

    void unknownStatus();

    void newMsg(const QString& sender, const QString& msg, const QString& status);

    void users(const Handler::StringMap& );

    void newInvite(const QString& userName);

    void startServer();

    void startClient(const QString& ip);

public:
    Handler() = default;

    nlohmann::json request(const std::string &request);

    nlohmann::json reply(const std::string& sender, const std::string &reply, Requests requestType);
};

#endif //TCPCLIENT_HANDLER_H
