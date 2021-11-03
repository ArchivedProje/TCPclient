// Copyright 2021 byteihq <kotov038@gmail.com>

#include <MainWindow.h>
#include <QApplication>
#include <memory>
#include <boost/asio.hpp>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    auto ioService = std::make_shared<boost::asio::io_service>();
    MainWindow mW(ioService);
    ioService->run();
    return app.exec();
}
