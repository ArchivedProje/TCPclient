// Copyright 2021 byteihq <kotov038@gmail.com>

#include <ServerWindow.h>

ServerWindow::ServerWindow(std::shared_ptr<Connection> connection, QWidget *parent) : Resizable(parent, 640, 480),
                                                                                      connection_(
                                                                                              std::move(connection)),
                                                                                      gridLayout_(
                                                                                              std::make_unique<QGridLayout>(
                                                                                                      this)),
                                                                                      infoWidget_(
                                                                                              std::make_unique<QListWidget>()),
                                                                                      lineEdit_(
                                                                                              std::make_unique<QLineEdit>()),
                                                                                      sendBtn_(
                                                                                              std::make_unique<QPushButton>(
                                                                                                      "Send", this)) {

    gridLayout_->addWidget(infoWidget_.get(), 0, 0, 10, 2);
    gridLayout_->addWidget(lineEdit_.get(), 10, 0);
    gridLayout_->addWidget(sendBtn_.get(), 10, 1);

    connect(sendBtn_.get(), &QPushButton::clicked, this, &ServerWindow::sendBtnClicked);
    //connect(exitBtn_.get(), &QPushButton::clicked, this, &ServerWindow::exitBtnClicked);
}

void ServerWindow::setSender(const std::string &sender) {
    sender_ = sender;
}

void ServerWindow::sendBtnClicked() {
    connection_->sendMessage(connection_->handler_->reply(sender_, lineEdit_->text().toStdString()));
    infoWidget_->addItem(lineEdit_->text());
    lineEdit_->clear();
}
