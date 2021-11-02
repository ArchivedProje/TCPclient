// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_USERSWINDOW_H
#define TCPCLIENT_USERSWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <Resizable.h>
#include <StyleSettings.h>
#include <ServerConnection.h>

class MainWindow;

class UsersWindow : public Resizable {
    Q_OBJECT
private:
    friend class MainWindow;
    std::shared_ptr<ServerConnection> connection_;
    std::unique_ptr<QGridLayout> qgrid_;
    std::map<std::string, std::unique_ptr<QPushButton>> buttons_;
    std::string sender_;
    using upQL = std::unique_ptr<QLabel>;
    upQL nameLabel_;
    upQL statusLabel_;
    std::vector<std::pair<upQL, upQL>> namesStatuses_;
    void setSender(const std::string& sender);
private slots:
    void setDarkMode();

    void setLightMode();

    void btnClicked(const QString& user);
public:
    explicit UsersWindow(QWidget *parent, std::shared_ptr<ServerConnection> connection, Mode mode);

    void Load(const std::map<std::string, std::string>& users);
};

#endif //TCPCLIENT_USERSWINDOW_H
