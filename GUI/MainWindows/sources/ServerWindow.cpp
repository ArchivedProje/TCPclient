// Copyright 2021 byteihq <kotov038@gmail.com>

#include <ServerWindow.h>

ServerWindow::ServerWindow(QWidget *parent) : Resizable(parent, 380, 200), gridLayout_(std::make_unique<QGridLayout>(this)),
                                              infoWidget_(std::make_unique<QListWidget>()),
                                              lineEdit_(std::make_unique<QLineEdit>()),
                                              sendBtn_(std::make_unique<QPushButton>("Send", this)),
                                              usersBtn_(std::make_unique<QPushButton>("Users", this)),
                                              statBtn_(std::make_unique<QPushButton>("Stats", this)),
                                              exitBtn_(std::make_unique<QPushButton>("Exit", this)) {

    gridLayout_->addWidget(infoWidget_.get(), 0, 0, 3, 2);
    gridLayout_->addWidget(usersBtn_.get(),0, 2);
    gridLayout_->addWidget(statBtn_.get(), 1, 2);
    gridLayout_->addWidget(exitBtn_.get(),2, 2);
    gridLayout_->addWidget(lineEdit_.get(),3, 0);
    gridLayout_->addWidget(sendBtn_.get(),3, 1);

    connect(exitBtn_.get(), &QPushButton::clicked, this, &ServerWindow::exitBtnClicked);
}

void ServerWindow::exitBtnClicked() {
    close();
    emit closeWindow();
}
