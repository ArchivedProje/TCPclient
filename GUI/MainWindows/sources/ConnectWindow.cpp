
#include <ConnectWindow.h>

ConnectWindow::ConnectWindow(QWidget *parent) : QWidget(parent), qvbox_(new QVBoxLayout(this)),
                                                qhboxIp_(new QHBoxLayout), qhboxLogin_(new QHBoxLayout),
                                                qhboxPass_(new QHBoxLayout), qhboxButtons_(new QHBoxLayout),
                                                ipLabel_(new QLabel("Ip:", this)),
                                                loginLabel_(new QLabel("Login:", this)),
                                                passLabel_(new QLabel("Password:", this)), ipLine_(new QLineEdit),
                                                loginLine_(new QLineEdit), passLine_(new QLineEdit),
                                                connectBtn_(new QPushButton("Connect", this)),
                                                exitBtn_(new QPushButton("Exit", this)) {

    resize(150, 100);

    qhboxIp_->addWidget(ipLabel_);
    qhboxIp_->addWidget(ipLine_);

    qhboxLogin_->addWidget(loginLabel_);
    qhboxLogin_->addWidget(loginLine_);

    qhboxPass_->addWidget(passLabel_);
    passLine_->setEchoMode(QLineEdit::Password);
    qhboxPass_->addWidget(passLine_);

    qhboxButtons_->addWidget(connectBtn_);
    qhboxButtons_->addWidget(exitBtn_);

    qvbox_->addLayout(qhboxIp_);
    qvbox_->addLayout(qhboxLogin_);
    qvbox_->addLayout(qhboxPass_);
    qvbox_->addLayout(qhboxButtons_);
}

ConnectWindow::~ConnectWindow() {
    delete qvbox_;
    delete qhboxIp_;
    delete qhboxLogin_;
    delete qhboxPass_;
    delete qhboxButtons_;
    delete ipLabel_;
    delete loginLabel_;
    delete passLabel_;
    delete ipLine_;
    delete loginLine_;
    delete passLine_;
    delete connectBtn_;
    delete exitBtn_;
}
