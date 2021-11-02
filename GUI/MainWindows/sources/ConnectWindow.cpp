// Copyright 2021 byteihq <kotov038@gmail.com>

#include <ConnectWindow.h>
#include <QMessageBox>
#include <Handler.h>

ConnectWindow::ConnectWindow(std::shared_ptr<ServerConnection> connection, QWidget *parent) : Resizable(parent, 245, 189), connection_(std::move(connection)),
                                                                        ipLabel_(std::make_unique<QLabel>("Ip:", this)),
                                                                        portLabel_(std::make_unique<QLabel>("Port:",
                                                                                                            this)),
                                                                        loginLabel_(std::make_unique<QLabel>("Login:",
                                                                                                             this)),
                                                                        passLabel_(std::make_unique<QLabel>("Password:",
                                                                                                            this)),
                                                                        ipLine_(std::make_unique<QLineEdit>()),
                                                                        portLine_(std::make_unique<QLineEdit>()),
                                                                        loginLine_(std::make_unique<QLineEdit>()),
                                                                        passLine_(std::make_unique<QLineEdit>()),
                                                                        connectBtn_(
                                                                                std::make_unique<QPushButton>("Connect",
                                                                                                              this)),
                                                                        exitBtn_(std::make_unique<QPushButton>("Exit",
                                                                                                               this)),
                                                                        gridLayout_(
                                                                                std::make_unique<QGridLayout>(this)) {


    gridLayout_->addWidget(ipLabel_.get(), 0, 0);
    gridLayout_->addWidget(ipLine_.get(), 0, 1);

    gridLayout_->addWidget(ipLabel_.get(), 1, 0);
    gridLayout_->addWidget(ipLine_.get(), 1, 1);

    gridLayout_->addWidget(portLabel_.get(), 2, 0);
    gridLayout_->addWidget(portLine_.get(), 2, 1);

    loginLine_->setText("user1");
    passLine_->setText("1u23456");

    gridLayout_->addWidget(loginLabel_.get(), 3, 0);
    gridLayout_->addWidget(loginLine_.get(), 3, 1);

    gridLayout_->addWidget(passLabel_.get(), 4, 0);
    passLine_->setEchoMode(QLineEdit::Password);
    gridLayout_->addWidget(passLine_.get(), 4, 1);

    gridLayout_->addWidget(connectBtn_.get(), 5, 0);
    gridLayout_->addWidget(exitBtn_.get(), 5, 1);

    connect(connectBtn_.get(), &QPushButton::clicked, this, &ConnectWindow::connectBtnClicked);
    connect(exitBtn_.get(), &QPushButton::clicked, this, &ConnectWindow::exitBtnClicked);

    connect(connection_->handler_.get(), &Handler::authorizeFailed, this, &ConnectWindow::showAuthFailed);
    connect(connection_->handler_.get(), &Handler::unknownStatus, this, &ConnectWindow::showUnStatus);
}

void ConnectWindow::exitBtnClicked() {
    close();
    emit closeWindow();
}

void ConnectWindow::connectBtnClicked() {
    bool fieldsEmpty = ipLine_->text().isEmpty() || portLine_->text().isEmpty() || loginLine_->text().isEmpty() ||
                       passLine_->text().isEmpty();
    if (fieldsEmpty) {
        showErrWindow("Fill in all the fields!");
        return;
    }
    int port = portLine_->text().toInt();
    if (port <= 0 || port > 65'536) {
        showErrWindow("Port number is wrong");
        return;
    }
    int status = connection_->Connect(ipLine_->text().toStdString(), port);
    if (status == -2) {
        showErrWindow("Server not responding");
        return;
    }
    if (status == -1) {
        showErrWindow("Ip is wrong");
        return;
    }
    status = connection_->authorize(loginLine_->text().toStdString(), passLine_->text().toStdString());
    if (status == -1) {
        showErrWindow("Error sending message");
        return;
    }

    emit startListening();
}

void ConnectWindow::setIp(const std::string &ip) {
    ipLine_->setText(QString::fromStdString(ip));
}

void ConnectWindow::setPort(size_t port) {
    portLine_->setText(QString::number(port));
}

void ConnectWindow::showAuthFailed() {
    showErrWindow("Authorised failed. Wrong login or password");
}

void ConnectWindow::showUnStatus() {
    showErrWindow("Server sent message with unknown status");
}

void ConnectWindow::showErrWindow(const std::string &errMsg) {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Error");
    msgBox.setText(QString::fromStdString(errMsg));
    msgBox.exec();
}
