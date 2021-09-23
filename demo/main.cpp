// Copyright 2021 byteihq <kotov038@gmail.com>

#include <MainWindow.h>
#include <Connection.h>
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    boost::asio::io_service ioService;
    Connection connection(ioService);
    MainWindow mW(connection);
    return app.exec();
}
