//

#ifndef TCPCLIENT_SERVER_H
#define TCPCLIENT_SERVER_H

#include <boost/asio.hpp>
#include <memory>
#include <QObject>

using boost::asio::ip::tcp;

class Server : public QObject {
private:
    std::shared_ptr<boost::asio::io_service> ioService_;
    tcp::acceptor acceptor_;
    tcp::socket socket_;
    boost::asio::streambuf data_;
public:
    explicit Server(const std::shared_ptr<boost::asio::io_service>& ioService);
    void accept();
    void getMessage();
};

#endif //TCPCLIENT_SERVER_H
