// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_USERSWINDOW_H
#define TCPCLIENT_USERSWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QGridLayout>
#include <QPushButton>
#include <map>
#include <string>
#include <memory>
#include <Resizable.h>
#include <StyleSettings.h>
#include <Connection.h>

class MainWindow;

class UsersWindow : public Resizable {
    Q_OBJECT
private:
    friend class MainWindow;
    std::shared_ptr<Connection> connection_;
    std::unique_ptr<QGridLayout> qgrid_;
    std::unique_ptr<QTableWidget> table_;
    std::map<std::string, std::unique_ptr<QPushButton>> buttons_;
    std::string sender_;

    void setSender(const std::string& sender);
private slots:
    void setDarkMode();

    void setLightMode();

    void btnClicked(const QString& user);
public:
    explicit UsersWindow(QWidget *parent, std::shared_ptr<Connection> connection, Mode mode);

    void Load(const std::map<std::string, std::string>& users);
};

#endif //TCPCLIENT_USERSWINDOW_H
