// Copyright 2021 byteihq <kotov038@gmail.com>

#include <UserConversation.h>
#include <QMessageBox>
#include <QMenu>
#include <QApplication>
#include <QClipboard>
#include <FileSettings.h>
#include <fstream>
#include <boost/array.hpp>
#include <iostream>

UserConversation::UserConversation(QWidget *parent, std::shared_ptr<QThread> clientThread,
                                   std::shared_ptr<QThread> serverThread,
                                   std::shared_ptr<boost::asio::io_service> &ioService, Mode mode) :
        Resizable(parent,
                  640, 480),
        ioService_(ioService),
        clientConnection_(std::make_unique<ClientConnection>()),
        serverConnection_(std::make_unique<Server>(ioService)),
        clientThread_(std::move(clientThread)),
        serverThread_(std::move(serverThread)),
        qgrid_(std::make_unique<QGridLayout>(this)),
        leftList_(std::make_unique<QListWidget>()),
        rightList_(std::make_unique<QListWidget>()),
        progress_(std::make_unique<QProgressBar>()),
        lineEdit_(std::make_unique<QLineEdit>()),
        sendBtn_(std::make_unique<QPushButton>("Send", this)),
        disconnectBtn_(std::make_unique<QPushButton>("Disconnect", this)),
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

    progress_->setStyleSheet("color: green;");

    rightList_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(rightList_.get(), &QWidget::customContextMenuRequested, this,
            &UserConversation::showRightContextMenu);

    leftList_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(leftList_.get(), &QWidget::customContextMenuRequested, this,
            &UserConversation::showLeftContextMenu);

    clientConnection_->moveToThread(clientThread_.get());
    connect(clientThread_.get(), &QThread::started, clientConnection_.get(), &ClientConnection::listen);
    serverConnection_->moveToThread(serverThread_.get());
    connect(serverThread_.get(), &QThread::started, serverConnection_.get(), &Server::listen);

    qRegisterMetaType<Handler::StringList>("Handler::StringList");
    connect(serverConnection_->handler_.get(), &Handler::newUserMsg, this, &UserConversation::showNewMsg);
    connect(serverConnection_->handler_.get(), &Handler::connectionAbort, this,
            &UserConversation::disconnectBtnClicked);
    connect(serverConnection_->handler_.get(), &Handler::sendAllFiles, this, &UserConversation::sendAllFiles);
    connect(serverConnection_->handler_.get(), &Handler::setAllFiles, this, &UserConversation::setAllFiles);
    connect(serverConnection_->handler_.get(), &Handler::sendFile, this, &UserConversation::sendFile);
    connect(serverConnection_->handler_.get(), &Handler::noFile, this, &UserConversation::noFile);
    qRegisterMetaType<Handler::Array>("Handler::Array");
    qRegisterMetaType<Handler::StreamSize>("Handler::StreamSize");
    connect(serverConnection_->handler_.get(), &Handler::setFile, this, &UserConversation::setFile);

    connect(clientConnection_->handler_.get(), &Handler::newUserMsg, this, &UserConversation::showNewMsg);
    connect(clientConnection_->handler_.get(), &Handler::connectionAbort, this,
            &UserConversation::disconnectBtnClicked);
    connect(clientConnection_->handler_.get(), &Handler::sendAllFiles, this, &UserConversation::sendAllFiles);
    connect(clientConnection_->handler_.get(), &Handler::setAllFiles, this, &UserConversation::setAllFiles);
    connect(clientConnection_->handler_.get(), &Handler::sendFile, this, &UserConversation::sendFile);
    connect(clientConnection_->handler_.get(), &Handler::noFile, this, &UserConversation::noFile);
    connect(clientConnection_->handler_.get(), &Handler::setFile, this, &UserConversation::setFile);

    connect(sendBtn_.get(), &QPushButton::clicked, this, &UserConversation::sendBtnClicked);
    connect(lineEdit_.get(), &QLineEdit::returnPressed, this, &UserConversation::sendBtnClicked);

    connect(disconnectBtn_.get(), &QPushButton::clicked, this, &UserConversation::disconnectBtnClicked);
}

void UserConversation::sendMsg(const nlohmann::json &msg) {
    switch (connectionMode_) {
        case ServerMode:
            serverConnection_->sendMessage(msg);
            break;
        case ClientMode:
            clientConnection_->sendMessage(msg);
            break;
    }
}

void UserConversation::sendBtnClicked() {
    if (lineEdit_->text().isEmpty()) {
        return;
    }
    ++msgNumber_;
    switch (connectionMode_) {
        case ServerMode:
            serverConnection_->sendMessage(
                    serverConnection_->handler_->reply(sender_, lineEdit_->text().toStdString(), Requests::UserMsg));
            break;
        case ClientMode:
            clientConnection_->sendMessage(
                    clientConnection_->handler_->reply(sender_, lineEdit_->text().toStdString(), Requests::UserMsg));
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
    clientThread_->start();
    nlohmann::json msg = {
            {"sender", sender_},
            {"type",   Requests::GetAllFiles},
            {"data",   Replies::GetAllFiles::GetAllFiles}
    };
    sendMsg(msg);
    show();
}

void UserConversation::startServer() {
    connectionMode_ = ConnectionMode::ServerMode;
    serverConnection_->accept();
    serverThread_->start();
    nlohmann::json msg = {
            {"sender", sender_},
            {"type",   Requests::GetAllFiles},
            {"data",   Replies::GetAllFiles::GetAllFiles}
    };
    sendMsg(msg);
    show();
}

void UserConversation::showNewMsg(const QString &sender, const QString &msg) {
    ++msgNumber_;
    rightList_->addItem(sender + ": " + msg);
}

void UserConversation::showRightContextMenu(const QPoint &point) {
    if (rightList_->selectedItems().size() == 1) {
        QPoint globalPos = mapToGlobal(point);
        globalPos.setX(globalPos.x() + QWidget::width() / 2);
        QMenu myMenu;
        myMenu.addAction("Reply", this, &UserConversation::actionReply);
        myMenu.addAction("Copy", this, &UserConversation::actionCopy);
        myMenu.exec(globalPos);
    }
}

void UserConversation::actionReply() {
    lineEdit_->setText(" <Reply> " + rightList_->selectedItems().first()->text() + " </Reply> ");
    rightList_->clearSelection();
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
    rightList_->clearSelection();
}

void UserConversation::showLeftContextMenu(const QPoint &point) {
    if (leftList_->selectedItems().size() == 1) {
        QPoint globalPos = mapToGlobal(point);
        globalPos.setX(globalPos.x());
        QMenu myMenu;
        myMenu.addAction("Get", this, &UserConversation::actionGet);
        myMenu.exec(globalPos);
    }
}

void UserConversation::actionGet() {
    nlohmann::json msg = {
            {"sender", sender_},
            {"type",   Requests::GetFile},
            {"data",   Replies::GetFile::GetFile},
            {"path",   leftList_->selectedItems().first()->text().toStdString()}
    };
    leftList_->clearSelection();
    sendMsg(msg);
}

void UserConversation::disconnectBtnClicked() {
    switch (connectionMode_) {
        case ServerMode:
            sendMsg(serverConnection_->handler_->reply(sender_, "", Requests::Disconnect));
            serverConnection_->reload(ioService_);
            serverThread_->terminate();
            break;
        case ClientMode:
            sendMsg(clientConnection_->handler_->reply(sender_, "", Requests::Disconnect));
            clientConnection_->reload();
            clientThread_->terminate();
            break;
    }
    rightList_->clear();
    msgNumber_ = 0;
    leftList_->clear();
    close();
}

void UserConversation::sendFile(const QString &path) {
    nlohmann::json msg = {
            {"sender", sender_},
            {"type",   Requests::GetFile},
            {"data",   Replies::GetFile::TakeFile},
            {"status", Replies::GetFile::FileExists}
    };
    std::ifstream file;
    file.open(path.toStdString(), std::ios::binary);
    if (!file.is_open()) {
        msg["status"] = Replies::GetFile::NoFile;
        sendMsg(msg);
        return;
    }
    boost::filesystem::path bPath = path.toStdString();
    msg["name"] = bPath.filename().string();
    msg["size"] = static_cast<int>(file.tellg());
    const size_t frameSize = 1000u;
    boost::array<char, frameSize> buffer{};
    size_t i = 1;
    std::streamsize size;
    while (file.read(buffer.c_array(), static_cast<std::streamsize>(buffer.size()))) {
        size = file.gcount();
        sendMsg(msg);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        sendFileData(buffer.data(), size);
        std::cerr << i << ' ' << size << ' ' << buffer.c_array() << std::endl;
        ++i;
        setFile(QString::fromStdString(bPath.filename().string()), buffer, 1000, size);
    }
    size = file.gcount();
    sendMsg(msg);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    sendFileData(buffer.c_array(), size);
    std::cerr << i << ' ' << size << ' ' << buffer.data() << std::endl;
    ++i;
    setFile(QString::fromStdString(bPath.filename().string()), buffer, 1000, size);
}

void UserConversation::sendAllFiles() {
    auto files = FileSettings::getFiles();
    auto status = files.empty() ? Replies::GetAllFiles::NoFiles : Replies::GetAllFiles::TakeAllFiles;
    nlohmann::json msg = {
            {"sender", sender_},
            {"type",   Requests::GetAllFiles},
            {"data",   Replies::GetAllFiles::TakeAllFiles},
            {"status", status},
            {"files",  files}
    };
    sendMsg(msg);
}

void UserConversation::setAllFiles(const Handler::StringList &paths) {
    for (const auto &path: paths) {
        leftList_->addItem(path);
    }
}

void UserConversation::noFile(const QString &path) {
    leftList_->clearSelection();
    for (int row = 0; row < leftList_->count(); ++row) {
        if (leftList_->item(row)->text() == path) {
            leftList_->item(row)->setBackgroundColor(QColor(160, 0, 0));
            break;
        }
    }
}

void UserConversation::setFile(const QString &name, const Handler::Array& data, int maxSize, Handler::StreamSize gcount) {
    auto path = "Files/" + name.toStdString();
    std::ifstream check(path);
    if (!check.is_open()) {
        std::ofstream create(path);
        create.close();
        check.close();
        progress_->setMaximum(maxSize);
        progress_->setValue(0);
    } else if (static_cast<int>(check.tellg()) == maxSize) {
        return;
    }
//    progress_->setValue(progress_->value() + data.size());
    std::ofstream file(path, std::ios::app | std::ios::binary);
    file.write(data.data(), gcount);
    file.close();
}

void UserConversation::sendFileData(const char *data, size_t size) {
    switch (connectionMode_) {
        case ServerMode:
            serverConnection_->sendFileData(data, size);
            break;
        case ClientMode:
            clientConnection_->sendFileData(data, size);
            break;
    }
}
