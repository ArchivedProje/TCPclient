// Copyright 2021 byteihq <kotov038@gmail.com>

#include <ServerWindow.h>

ServerWindow::ServerWindow(QWidget *parent) : QWidget(parent), gridLayout_(std::make_unique<QGridLayout>(this)),
                                              infoWidget_(std::make_unique<QListWidget>()),
                                              lineEdit_(std::make_unique<QLineEdit>()),
                                              sendBtn_(std::make_unique<QPushButton>("Send", this)),
                                              exitBtn_(std::make_unique<QPushButton>("Exit", this)),
                                              usersBtn_(std::make_unique<QPushButton>("Users", this)) {
    gridLayout_->addWidget(infoWidget_.get(), 0, 0, 1, 2);
    gridLayout_->addWidget(usersBtn_.get(), 0, 2);
    gridLayout_->addWidget(lineEdit_.get(), 1, 0);
    gridLayout_->addWidget(sendBtn_.get(), 1, 1);
    gridLayout_->addWidget(exitBtn_.get(), 2, 0);
}
