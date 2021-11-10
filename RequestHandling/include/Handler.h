//Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_HANDLER_H
#define TCPCLIENT_HANDLER_H

#include <string>
#include <QObject>
#include <map>
#include <QString>
#include <nlohmann/json.hpp>
#include <NetworkCommunication.h>
#include <boost/array.hpp>
class Handler : public QObject {
Q_OBJECT
private:
    void showErrMsg(const std::string& msg);

    struct File {
        QString name_;
        int maxSize_;
    };
    File file_;
    bool fileData_;
public:
    typedef std::map<std::string, std::string> StringMap;
    typedef QList<QString> StringList;
    typedef boost::array<char, 1000> Array;
    typedef std::streamsize StreamSize;
signals:

    void authorizeFailed();

    void authorizeSucceed();

    void unknownStatus();

    void newMsg(const QString& sender, const QString& msg, const QString& status);

    void newUserMsg(const QString& sender, const QString& msg);

    void users(const Handler::StringMap& );

    void newInvite(const QString& userName);

    void startServer();

    void startClient(const QString& ip);

    void connectionAbort();

    void sendAllFiles();

    void setAllFiles(const Handler::StringList& paths);

    void sendFile(const QString& path);

    void setFile(const QString &name, const Handler::Array& data, int maxSize, Handler::StreamSize gcount);

    void noFile(const QString& path);

public:
    Handler();

    void request(const std::string &request, std::istream& stream);

    nlohmann::json reply(const std::string& sender, const std::string &reply, Requests requestType);
};

#endif //TCPCLIENT_HANDLER_H
