// Copyright 2021 byteihq <kotov038@gmail.com>

#include <ConnectWindow.h>
#include <QMessageBox>

ConnectWindow::ConnectWindow(Connection& connection, QWidget *parent) : QWidget(parent), connection_(connection), qhbox_(new QHBoxLayout(this)),
                                                leftQvbox_(new QVBoxLayout), rightQvbox_(new QVBoxLayout),
                                                ipLabel_(new QLabel("Ip:", this)),
                                                portLabel_(new QLabel("Port:", this)),
                                                loginLabel_(new QLabel("Login:", this)),
                                                passLabel_(new QLabel("Password:", this)), ipLine_(new QLineEdit),
                                                portLine_(new QLineEdit),
                                                loginLine_(new QLineEdit), passLine_(new QLineEdit),
                                                connectBtn_(new QPushButton("Connect", this)),
                                                exitBtn_(new QPushButton("Exit", this)) {

    resize(150, 100);

    leftQvbox_->addWidget(ipLabel_);
    rightQvbox_->addWidget(ipLine_);

    leftQvbox_->addWidget(portLabel_);
    rightQvbox_->addWidget(portLine_);

    leftQvbox_->addWidget(loginLabel_);
    rightQvbox_->addWidget(loginLine_);

    leftQvbox_->addWidget(passLabel_);
    passLine_->setEchoMode(QLineEdit::Password);
    rightQvbox_->addWidget(passLine_);

    leftQvbox_->addWidget(connectBtn_);
    rightQvbox_->addWidget(exitBtn_);

    qhbox_->addLayout(leftQvbox_);
    qhbox_->addLayout(rightQvbox_);

    connect(connectBtn_, &QPushButton::clicked, this, &ConnectWindow::connectBtnClicked);
    connect(exitBtn_, &QPushButton::clicked, this, &ConnectWindow::exitBtnClicked);
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
}

ConnectWindow::~ConnectWindow() {
    delete qhbox_;
    delete leftQvbox_;
    delete rightQvbox_;
    delete ipLabel_;
    delete loginLabel_;
    delete passLabel_;
    delete ipLine_;
    delete loginLine_;
    delete passLine_;
    delete connectBtn_;
    delete exitBtn_;
}
