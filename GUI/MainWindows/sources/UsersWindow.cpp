// Copyright 2021 byteihq <kotov038@gmail.com>

#include <UsersWindow.h>

UsersWindow::UsersWindow(QWidget *parent, std::shared_ptr<Connection> connection, Mode mode) : Resizable(parent, 100,
                                                                                                         100),
                                                                                               connection_(std::move(
                                                                                                       connection)),
                                                                                               qgrid_(std::make_unique<QGridLayout>(
                                                                                                       this)),
                                                                                               nameLabel_(
                                                                                                       std::make_unique<QLabel>(
                                                                                                               "Name",
                                                                                                               this)),
                                                                                               statusLabel_(
                                                                                                       std::make_unique<QLabel>(
                                                                                                               "Status",
                                                                                                               this)) {
    if (mode == Mode::Dark) {
        StyleSettings::setDarkMode(this);
    } else {
        StyleSettings::setLightMode(this);
    }
    qgrid_->addWidget(nameLabel_.get(), 0, 0);
    qgrid_->addWidget(statusLabel_.get(), 0, 1);
}

void UsersWindow::Load(const std::map<std::string, std::string> &users) {
    namesStatuses_.clear();
    size_t row = 1u;
    size_t maxWidth = 0u;
    for (const auto &user: users) {
        namesStatuses_.emplace_back(std::make_unique<QLabel>(QString::fromStdString(user.first)),
                                  std::make_unique<QLabel>(QString::fromStdString(user.second)));
        qgrid_->addWidget(namesStatuses_.back().first.get(), row, 0);
        qgrid_->addWidget(namesStatuses_.back().second.get(), row, 1);
        maxWidth = std::max(maxWidth, user.first.size() + user.second.size() + 12);
        if (user.second == "connected") {
            buttons_.insert({user.first, std::make_unique<QPushButton>("connect")});
            qgrid_->addWidget( buttons_.at(user.first).get(), row, 2);
        }
        ++row;
    }

    for (const auto &button: buttons_) {
        connect(button.second.get(), &QPushButton::clicked, this, [this, &button]() {
            btnClicked(QString::fromStdString(button.first));
        });
    }

    setWidth(maxWidth * 12);
    setHeight(row * 30);
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

void UsersWindow::btnClicked(const QString &user) {
    nlohmann::json msg = {
            {"sender", sender_},
            {"type",   Requests::ConnectToUser},
            {"data",   Replies::ConnectToUser::Invite},
            {"name",   user.toStdString()}
    };
    connection_->sendMessage(msg);
}
