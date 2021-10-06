// Copyright 2021 byteihq <kotov038@gmail.com>

#include <ConnectWindow.h>
#include <QMessageBox>

ConnectWindow::ConnectWindow(Connection &connection, QWidget *parent) : QWidget(parent), connection_(connection),
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
                                                                        gridLayout_(std::make_unique<QGridLayout>(this)){

    resize(150, 100);
    gridLayout_->addWidget(ipLabel_.get(), 0, 0);
    gridLayout_->addWidget(ipLine_.get(), 0, 1);

    gridLayout_->addWidget(ipLabel_.get(), 1, 0);
    gridLayout_->addWidget(ipLine_.get(), 1, 1);

    gridLayout_->addWidget(portLabel_.get(), 2, 0);
    gridLayout_->addWidget(portLine_.get(), 2, 1);

    gridLayout_->addWidget(loginLabel_.get(), 3, 0);
    gridLayout_->addWidget(loginLine_.get(), 3, 1);

    gridLayout_->addWidget(passLabel_.get(), 4, 0);
    passLine_->setEchoMode(QLineEdit::Password);
    gridLayout_->addWidget(passLine_.get(), 4, 1);

    gridLayout_->addWidget(connectBtn_.get(), 5, 0);
    gridLayout_->addWidget(exitBtn_.get(), 5, 1);

    connect(connectBtn_.get(), &QPushButton::clicked, this, &ConnectWindow::connectBtnClicked);
    connect(exitBtn_.get(), &QPushButton::clicked, this, &ConnectWindow::exitBtnClicked);
}

void ConnectWindow::exitBtnClicked() {
    close();
    emit closeWindow();
}

void ConnectWindow::connectBtnClicked() {
    bool fieldsEmpty = ipLine_->text().isEmpty() || portLine_->text().isEmpty() || loginLine_->text().isEmpty() ||
                       passLine_->text().isEmpty();
    QMessageBox msgBox;
    msgBox.setWindowTitle("Error");
    if (fieldsEmpty) {
        msgBox.setText("Fill in all the fields!");
        msgBox.exec();
        return;
    }
    int port = portLine_->text().toInt();
    if (port <= 0 || port > 65'536) {
        msgBox.setText("Port number is wrong");
        msgBox.exec();
        return;
    }
    int status = connection_.connect(ipLine_->text().toStdString(), port);
    if (status == -2) {
        msgBox.setText("Server not responding");
        msgBox.exec();
        return;
    }
    if (status == -1) {
        msgBox.setText("Ip is wrong");
        msgBox.exec();
        return;
    }
    status = connection_.authorize(loginLine_->text().toStdString(), passLine_->text().toStdString());
    if (status == -1) {
        msgBox.setText("Error sending message");
        msgBox.exec();
        return;
    }
}

void ConnectWindow::setIp(const std::string &ip) {
    ipLine_->setText(QString::fromStdString(ip));
}

void ConnectWindow::setPort(size_t port) {
    portLine_->setText(QString::number(port));
}
