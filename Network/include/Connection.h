// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_CONNECTION_H
#define TCPCLIENT_CONNECTION_H

#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <string>
#include <QObject>
#include <RequestHandler.h>
#include <memory>

using boost::asio::ip::tcp;

class ConnectWindow;

class Connection : public QObject {
    Q_OBJECT
private:
    friend class ConnectWindow;
    boost::asio::io_service ioService_;
    tcp::socket socket_;
    boost::asio::deadline_timer deadline_;
    boost::asio::streambuf data_;
    std::unique_ptr<RequestHandler> handler_;

    void checkDeadline();

    void getMessage();
public:
    Connection();

    int connect(const std::string &ip_, int port_);

    int authorize(const std::string &login, const std::string &password);

    void sendMessage(const std::string& msg);

public slots:
    void listen();
};

#endif //TCPCLIENT_CONNECTION_H
