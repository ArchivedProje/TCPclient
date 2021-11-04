// Copyright 2021 byteihq <kotov038@gmail.com>

#include <UserConversation.h>
#include <QMessageBox>
#include <QMenu>
#include <QApplication>
#include <QClipboard>

UserConversation::UserConversation(QWidget * parent, std::shared_ptr <QThread> clientThread,
                                   std::shared_ptr <QThread> serverThread, const std::shared_ptr <boost::asio::io_service> &ioService_, Mode mode) :
Resizable(parent,
640, 480),
clientConnection_ (std::make_unique<ClientConnection>()),
serverConnection_(std::make_unique<Server>(ioService_)),
clientThread_(std::move(clientThread)),
serverThread_(std::move(serverThread)),
qgrid_(std::make_unique<QGridLayout>(this)),
leftList_(std::make_unique<QListWidget>()),
rightList_(std::make_unique<QListWidget>()),
progress_(std::make_unique<QProgressBar>()),
lineEdit_(std::make_unique<QLineEdit>()),
sendBtn_(std::make_unique<QPushButton>("Send",this)),
disconnectBtn_(std::make_unique<QPushButton>("Disconnect",this)),
msgNumber_(0) {

    if (mode == Mode::Dark) {
        StyleSettings::setDarkMode(this);
    } else {
        StyleSettings::setLightMode(this);
    }

    qgrid_->addWidget(leftList_.get(), 0, 0, 3, 4);
    qgrid_->addWidget(rightList_.get(), 0, 4, 3, 4);
    qgrid_->addWidget(progress_.get(), 3, 0, 1, 4);
    qgrid_->addWidget(lineEdit_.get(), 3, 4, 1, 3);
    qgrid_->addWidget(sendBtn_.get(), 3, 7);
    qgrid_->addWidget(disconnectBtn_.get(), 4, 0, 1, 8);

    rightList_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(rightList_.get(), &QWidget::customContextMenuRequested, this,
            &UserConversation::ShowContextMenu);

    clientConnection_->moveToThread(clientThread_.get());
    connect(clientThread_.get(), &QThread::started, clientConnection_.get(), &ClientConnection::listen);
    serverConnection_->moveToThread(serverThread_.get());
    connect(serverThread_.get(), &QThread::started, serverConnection_.get(), &Server::listen);

    connect(sendBtn_.get(), &QPushButton::clicked, this, &UserConversation::sendBtnClicked);
    connect(lineEdit_.get(), &QLineEdit::returnPressed, this, &UserConversation::sendBtnClicked);

    connect(disconnectBtn_.get(), &QPushButton::clicked, this, &UserConversation::disconnectBtnClicked);
}

void UserConversation::sendBtnClicked() {
    if (lineEdit_->text().isEmpty()) {
        return;
    }
    ++msgNumber_;
    switch (connectionMode_) {
        case ServerMode:
            serverConnection_->sendMessage(serverConnection_->handler_->reply(sender_, lineEdit_->text().toStdString(), Requests::UserMsg));
            break;
        case ClientMode:
            clientConnection_->sendMessage(clientConnection_->handler_->reply(sender_, lineEdit_->text().toStdString(), Requests::UserMsg));
            break;
    }
    rightList_->addItem(QString::fromStdString(sender_) + ": " + lineEdit_->text());
    rightList_->item(msgNumber_ - 1)->setBackgroundColor(QColor(60, 100, 100));
    lineEdit_->clear();

}

void UserConversation::setSender(const std::string &sender) {
    sender_ = sender;
}

void UserConversation::setDarkMode() {
    StyleSettings::setDarkMode(this);
}

void UserConversation::setLightMode() {
    StyleSettings::setLightMode(this);
}

void UserConversation::startClient(const QString &ip) {
    show();
    connectionMode_ = ConnectionMode::ClientMode;
    auto status = clientConnection_->Connect(ip.toStdString(), 2002);
    if (status == -2) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Server not responding");
        msgBox.exec();
        return;
    }
    if (status == -1) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Ip is wrong");
        msgBox.exec();
        return;
    }
    connect(clientConnection_->handler_.get(), &Handler::newUserMsg, this, &UserConversation::showNewMsg);
    connect(clientConnection_->handler_.get(), &Handler::connectionAbort, this, &UserConversation::disconnectBtnClicked);
    clientThread_->start();
}

void UserConversation::startServer() {
    show();
    connectionMode_ = ConnectionMode::ServerMode;
    connect(serverConnection_->handler_.get(), &Handler::newUserMsg, this, &UserConversation::showNewMsg);
    connect(serverConnection_->handler_.get(), &Handler::connectionAbort, this, &UserConversation::disconnectBtnClicked);
    serverConnection_->accept();
    serverThread_->start();
}

void UserConversation::showNewMsg(const QString &sender, const QString &msg) {
    ++msgNumber_;
    rightList_->addItem(sender + ": " + msg);
}

void UserConversation::ShowContextMenu(const QPoint &point) {
    if (rightList_->selectedItems().size() == 1) {
        QPoint globalPos = mapToGlobal(point);
        globalPos.setX(globalPos.x() + 100);
        QMenu myMenu;
        myMenu.addAction("Reply", this, &UserConversation::actionReply);
        myMenu.addAction("Copy", this, &UserConversation::actionCopy);
        myMenu.exec(globalPos);
    }
}

void UserConversation::actionReply() {
    lineEdit_->setText(" <Reply> " + rightList_->selectedItems().first()->text() + " </Reply> ");
    lineEdit_->setFocus();
}

void UserConversation::actionCopy() {
    auto clipboard = QApplication::clipboard();

    std::string text = rightList_->selectedItems().first()->text().toStdString();
    text = text.substr(sender_.size() + 1, text.size() - sender_.size() - 1);

    clipboard->setText(QString::fromStdString(text), QClipboard::Clipboard);

    if (clipboard->supportsSelection()) {
        clipboard->setText(QString::fromStdString(text), QClipboard::Selection);
    }

#if defined(Q_OS_LINUX)
    std::this_thread::sleep_for(std::chrono::nanoseconds(1)); //workaround for copied text not being available...
#endif
}

void UserConversation::disconnectBtnClicked() {
    switch (connectionMode_) {
        case ServerMode:
            serverConnection_->sendMessage(serverConnection_->handler_->reply(sender_, "", Requests::Disconnect));
            serverThread_->terminate();
            break;
        case ClientMode:
            clientConnection_->sendMessage(clientConnection_->handler_->reply(sender_, "", Requests::Disconnect));
            clientThread_->terminate();
            break;
    }
    close();
}
