//

#include <ConnectionInvite.h>

ConnectionInvite::ConnectionInvite(QWidget *parent, Mode mode) : Resizable(parent, 100, 100),
                                                                 qgrid_(std::make_unique<QGridLayout>(this)),
                                                                 qlabel_(std::make_unique<QLabel>()),
                                                                 acceptBtn_(
                                                                         std::make_unique<QPushButton>("Accept", this)),
                                                                 declineBtn_(std::make_unique<QPushButton>("Decline",
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
}

void ConnectionInvite::setDarkMode() {
    StyleSettings::setDarkMode(this);
}

void ConnectionInvite::setLightMode() {
    StyleSettings::setLightMode(this);
}

void ConnectionInvite::newInvite(const std::string &userName) {
    qlabel_->setText(QString::fromStdString(userName) + " wants to connect to you");
    show();
}
