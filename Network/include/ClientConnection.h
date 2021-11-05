// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_CLIENTCONNECTION_H
#define TCPCLIENT_CLIENTCONNECTION_H

#include <Connection.h>
#include <Handler.h>
#include <memory>
#include <QObject>

class ClientConnection : public Connection {
public:
    ClientConnection() = default;

    void reload();
};

#endif //TCPCLIENT_CLIENTCONNECTION_H
