// Copyright 2021 byteihq <kotov038@gmail.com>

#include <ClientConnection.h>

void ClientConnection::reload() {
    socket_.reset();
    socket_ = std::make_shared<tcp::socket>(ioService_);
}
