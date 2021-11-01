// Copyright 2021 byteihq <kotov038@gmail.com>

#include <UsersWindow.h>

UsersWindow::UsersWindow(QWidget *parent, std::shared_ptr<Connection> connection, Mode mode) : Resizable(parent, 100, 100), connection_(std::move(connection)) {
    if (mode == Mode::Dark) {
        StyleSettings::setDarkMode(this);
    } else {
        StyleSettings::setLightMode(this);
    }
}

void UsersWindow::Load(const std::map<std::string, std::string> &users) {
    qgrid_.reset();
    qgrid_ = std::make_unique<QGridLayout>(this);
    table_.reset();
    table_ = std::make_unique<QTableWidget>(users.size(), 3, this);
    size_t row = 0u;
    size_t maxWidth = 0u;
    for (const auto &user: users) {
        table_->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(user.first)));
        table_->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(user.second)));
        maxWidth = std::max(maxWidth, user.first.size() + user.second.size() + 12);
        if (user.second == "connected") {
            buttons_.insert({user.first, std::make_unique<QPushButton>("connect")});
            table_->setCellWidget(row, 2, buttons_.at(user.first).get());
        }
        ++row;
    }

    for (const auto& button : buttons_) {
        connect(button.second.get(), &QPushButton::clicked, this, [this, &button]() {
            btnClicked(QString::fromStdString(button.first));
        });
    }

    setWidth(maxWidth * 12);
    setHeight(row * 55);
    table_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    table_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qgrid_->addWidget(table_.get(), 0, 0);
    table_->show();
}

void UsersWindow::setLightMode() {
    StyleSettings::setLightMode(this);
}

void UsersWindow::setDarkMode() {
    StyleSettings::setDarkMode(this);
}

void UsersWindow::setSender(const std::string &sender) {
    sender_ = sender;
}

void UsersWindow::btnClicked(const QString& user) {
    nlohmann::json msg = {
            {"sender", sender_},
            {"type", Requests::ConnectToUser},
            {"data", Replies::ConnectToUser::Invite},
            {"name", user.toStdString()}
    };
    connection_->sendMessage(msg.dump());
}
