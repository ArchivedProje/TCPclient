// Copyright 2021 byteihq <kotov038@gmail.com>

#include <Connection.h>
#include <boost/lambda/lambda.hpp>
#include <boost/bind/bind.hpp>
#include <nlohmann/json.hpp>

Connection::Connection() : socket_(ioService_), deadline_(ioService_) {
    deadline_.expires_at(boost::posix_time::pos_infin);
    checkDeadline();
}

int Connection::connect(const std::string &ip_, int port_) {
    /*
     * -2 - server not responding / the computer isn't connected to the Internet
     * -1 - wrong ip
     * 0 - everything is fine
     */
    boost::system::error_code ec;
    auto ip = boost::asio::ip::address::from_string(ip_, ec);
    if (ec) {
        return -1;
    }
    ec = boost::asio::error::would_block;
    deadline_.expires_from_now(boost::posix_time::seconds(2));
    socket_.async_connect(tcp::endpoint(ip, port_), boost::lambda::var(ec) = boost::lambda::_1);
    do ioService_.run_one(); while (ec == boost::asio::error::would_block);
    if (ec || !socket_.is_open()) {
        return -2;
    }
    return 0;
}

int Connection::authorize(const std::string &login, const std::string &password) {
    nlohmann::json msg = {
            {"sender", login},
            {"type",   "auth"},
            {"data",   {{"login", login}, {"pass", password}}}
    };
    boost::system::error_code ec;

    boost::asio::write(socket_, boost::asio::buffer(msg.dump() + '\n', msg.dump().size() + 1), ec);
    /*
     * -1 - error
     * 0 - message sent
     */
    return ec ? -1 : 0;
}

void Connection::checkDeadline() {
    if (deadline_.expires_at() <= boost::asio::deadline_timer::traits_type::now())
    {
        boost::system::error_code ignored_ec;
        socket_.close(ignored_ec);

        deadline_.expires_at(boost::posix_time::pos_infin);
    }
    deadline_.async_wait(boost::bind(&Connection::checkDeadline, this));
}
