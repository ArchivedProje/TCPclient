// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_CONNECTIONINVITE_H
#define TCPCLIENT_CONNECTIONINVITE_H

#include <Resizable.h>
#include <StyleSettings.h>
#include <ServerConnection.h>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <memory>
#include <string>

class MainWindow;

class ConnectionInvite : public Resizable {
Q_OBJECT
private:
    friend class MainWindow;

    std::unique_ptr<QGridLayout> qgrid_;
    std::unique_ptr<QLabel> qlabel_;
    using upPB = std::unique_ptr<QPushButton>;
    upPB acceptBtn_;
    upPB declineBtn_;
    std::string sender_;
    QString userName_;
    std::shared_ptr<ServerConnection> connection_;

    void setSender(const std::string &sender);

private slots:

    void setDarkMode();

    void setLightMode();

    void newInvite(const QString &userName);

    void acceptBtnClicked();

    void declineBtnClicked();

public:
    explicit ConnectionInvite(QWidget *parent, std::shared_ptr<ServerConnection> connection, Mode mode);
};

#endif //TCPCLIENT_CONNECTIONINVITE_H
