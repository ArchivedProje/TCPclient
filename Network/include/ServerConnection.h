// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_SERVERCONNECTION_H
#define TCPCLIENT_SERVERCONNECTION_H

#include <nlohmann/json.hpp>
#include <Handler.h>
#include <Connection.h>

using boost::asio::ip::tcp;

class ConnectWindow;
class ServerWindow;
class UsersWindow;
class MainWindow;

class ServerConnection : public QObject, public Connection {
    Q_OBJECT
private:
    friend class ConnectWindow;
    friend class ServerWindow;
    friend class UsersWindow;
    friend class MainWindow;
    std::unique_ptr<Handler> handler_;
    void getMessage();
public:
    ServerConnection();

    int authorize(const std::string &login, const std::string &password);

public slots:
    void listen();
};

#endif //TCPCLIENT_SERVERCONNECTION_H
