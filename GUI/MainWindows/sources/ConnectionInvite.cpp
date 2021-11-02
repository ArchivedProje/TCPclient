//

#include <ConnectionInvite.h>
#include <nlohmann/json.hpp>
#include <NetworkCommunication.h>

ConnectionInvite::ConnectionInvite(QWidget *parent, std::shared_ptr<Connection> connection, Mode mode) : Resizable(parent, 100, 100),
                                                                                                         connection_(
                                                                                                                 std::move(
                                                                                                                         connection)),
                                                                                                         qgrid_(std::make_unique<QGridLayout>(
                                                                                                                 this)),
                                                                                                         qlabel_(std::make_unique<QLabel>()),
                                                                                                         acceptBtn_(
                                                                                                                 std::make_unique<QPushButton>(
                                                                                                                         "Accept",
                                                                                                                         this)),
                                                                                                         declineBtn_(
                                                                                                                 std::make_unique<QPushButton>(
                                                                                                                         "Decline",
                                                                                                                         this)) {
    if (mode == Mode::Dark) {
        StyleSettings::setDarkMode(this);
    } else {
        StyleSettings::setLightMode(this);
    }
    setWindowModality(Qt::WindowModal);
    qgrid_->addWidget(qlabel_.get(), 0, 0, 1, 2);
    qgrid_->addWidget(acceptBtn_.get(), 1, 0);
    qgrid_->addWidget(declineBtn_.get(), 1, 1);

    connect(acceptBtn_.get(), &QPushButton::clicked, this, &ConnectionInvite::acceptBtnClicked);
    connect(declineBtn_.get(), &QPushButton::clicked, this, &ConnectionInvite::declineBtnClicked);
}

void ConnectionInvite::setDarkMode() {
    StyleSettings::setDarkMode(this);
}

void ConnectionInvite::setLightMode() {
    StyleSettings::setLightMode(this);
}

void ConnectionInvite::newInvite(const QString &userName) {
    userName_ = userName;
    qlabel_->setText(userName + " wants to connect to you");
    show();
}

void ConnectionInvite::setSender(const std::string &sender) {
    sender_ = sender;
}

void ConnectionInvite::acceptBtnClicked() {
    nlohmann::json msg = {
            {"sender", sender_},
            {"type",   Requests::ConnectToUser},
            {"data",   Replies::ConnectToUser::Accept},
            {"name", userName_.toStdString()}
    };
    connection_->sendMessage(msg);
    close();
}

void ConnectionInvite::declineBtnClicked() {
    nlohmann::json msg = {
            {"sender", sender_},
            {"type",   Requests::ConnectToUser},
            {"data",   Replies::ConnectToUser::Decline},
            {"name", userName_.toStdString()}
    };
    connection_->sendMessage(msg);
    close();
}

