// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_SERVERCONNECTION_H
#define TCPCLIENT_SERVERCONNECTION_H

#include <Connection.h>

using boost::asio::ip::tcp;

class ConnectWindow;

class ServerWindow;

class UsersWindow;

class MainWindow;

class ServerConnection : public Connection {
private:
    friend class ConnectWindow;

    friend class ServerWindow;

    friend class UsersWindow;

    friend class MainWindow;

public:
    ServerConnection() = default;

    int authorize(const std::string &login, const std::string &password);
};

#endif //TCPCLIENT_SERVERCONNECTION_H
