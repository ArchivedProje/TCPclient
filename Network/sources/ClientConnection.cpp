// Copyright 2021 byteihq <kotov038@gmail.com>

#include <ClientConnection.h>

void ClientConnection::reload() {
    socket_->close();
    socket_.reset(new tcp::socket(*ioService_));
}
