//

#ifndef TCPCLIENT_SERVER_H
#define TCPCLIENT_SERVER_H

#include <boost/asio.hpp>
#include <memory>
#include <QObject>
#include <nlohmann/json.hpp>
#include <Handler.h>

using boost::asio::ip::tcp;

class Server : public QObject {
private:
    tcp::acceptor acceptor_;
    tcp::socket socket_;
    boost::asio::streambuf data_;
    void getMessage();
public:
    std::unique_ptr<Handler> handler_;

    explicit Server(const std::shared_ptr<boost::asio::io_service>& ioService);

    void accept();

    void listen();

    void sendMessage(const nlohmann::json &msg);
};

#endif //TCPCLIENT_SERVER_H
