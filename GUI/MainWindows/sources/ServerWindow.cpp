// Copyright 2021 byteihq <kotov038@gmail.com>

#include <ServerWindow.h>
#include <NetworkCommunication.h>
#include <nlohmann/json.hpp>
#include <QMenu>
#include <QApplication>
#include <QClipboard>

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
                                                                                                      "Send", this)),
                                                                                      msgNumber_(0) {
    setWindowModality(Qt::WindowModal);
    gridLayout_->addWidget(infoWidget_.get(), 0, 0, 10, 2);
    gridLayout_->addWidget(lineEdit_.get(), 10, 0);
    gridLayout_->addWidget(sendBtn_.get(), 10, 1);

    infoWidget_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(infoWidget_.get(), SIGNAL(customContextMenuRequested(const QPoint&)), this,
            SLOT(ShowContextMenu(const QPoint&)));
    connect(connection_->handler_.get(), SIGNAL(newMsg(const QString&, const QString&, const QString&)), this,
            SLOT(showNewMsg(const QString&, const QString&, const QString&)));
    connect(sendBtn_.get(), &QPushButton::clicked, this, &ServerWindow::sendBtnClicked);
    connect(lineEdit_.get(), &QLineEdit::returnPressed, this, &ServerWindow::sendBtnClicked);
}

void ServerWindow::setSender(const std::string &sender) {
    sender_ = sender;
}

void ServerWindow::sendBtnClicked() {
    if (!lineEdit_->text().isEmpty()) {
        ++msgNumber_;
        connection_->sendMessage(connection_->handler_->reply(sender_, lineEdit_->text().toStdString(), Requests::Msg));
        infoWidget_->addItem(QString::fromStdString(sender_) + ": " + lineEdit_->text());
        infoWidget_->item(msgNumber_ - 1)->setBackgroundColor(QColor(60, 100, 100));
        lineEdit_->clear();
    }
}

void ServerWindow::ShowContextMenu(const QPoint &point) {
    if (infoWidget_->selectedItems().size() == 1) {
        QPoint globalPos = mapToGlobal(point);
        QMenu myMenu;
        myMenu.addAction("Reply", this, &ServerWindow::actionReply);
        myMenu.addAction("Copy", this, &ServerWindow::actionCopy);
        myMenu.exec(globalPos);
    }
}

void ServerWindow::actionReply() {
    lineEdit_->setText("<Reply> " + infoWidget_->selectedItems().first()->text() + " </Reply>");
    lineEdit_->setFocus();
}

void ServerWindow::actionCopy() {
    auto clipboard = QApplication::clipboard();

    std::string text = infoWidget_->selectedItems().first()->text().toStdString();
    text = text.substr(sender_.size() + 1, text.size() - sender_.size() - 1);

    clipboard->setText(QString::fromStdString(text), QClipboard::Clipboard);

    if (clipboard->supportsSelection()) {
        clipboard->setText(QString::fromStdString(text), QClipboard::Selection);
    }

#if defined(Q_OS_LINUX)
    std::this_thread::sleep_for(std::chrono::nanoseconds(1)); //workaround for copied text not being available...
#endif
}

void ServerWindow::actionDisconnect() {
    connection_->sendMessage(connection_->handler_->reply(sender_, "", Requests::Disconnect));
    emit closeWindow();
}

void ServerWindow::showNewMsg(const QString &sender, const QString &msg, const QString &status) {
    ++msgNumber_;
    infoWidget_->addItem(sender + ": " + msg);
    if (status == "Important") {
        infoWidget_->item(msgNumber_ - 1)->setBackgroundColor(QColor(255, 0, 0));
    }
}

void ServerWindow::actionGetUsers() {
    nlohmann::json msg = {
            {"sender", sender_},
            {"type",   Requests::GetUsers}
    };
    connection_->sendMessage(msg);
}
