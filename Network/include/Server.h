// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_SERVER_H
#define TCPCLIENT_SERVER_H

#include <boost/asio.hpp>
#include <memory>
#include <QObject>
#include <nlohmann/json.hpp>
#include <Handler.h>
#include <set>

using boost::asio::ip::tcp;

class Server : public QObject {
Q_OBJECT
private:
    std::shared_ptr<tcp::acceptor> acceptor_;
    std::shared_ptr<tcp::socket> socket_;
    boost::asio::streambuf data_;
    const std::string delim_;
    void getMessage();

public:
    std::unique_ptr<Handler> handler_;

    explicit Server(std::shared_ptr<boost::asio::io_service> &ioService);

    void accept();

    void sendMessage(const nlohmann::json &msg);

    void reload(std::shared_ptr<boost::asio::io_service> &ioService);

    void sendFileData(const char *data, size_t size);
    std::pair<boost::array<char, 1000>, size_t> readSome();

public slots:

    void listen();
};

#endif //TCPCLIENT_SERVER_H
