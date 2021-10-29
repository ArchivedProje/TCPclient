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

class MainWindow;

class UsersWindow : public Resizable {
private:
    friend class MainWindow;
    std::unique_ptr<QGridLayout> qgrid_;
    std::unique_ptr<QTableWidget> table_;
    std::map<std::string, std::unique_ptr<QPushButton>> buttons_;
private slots:
    void setDarkMode();

    void setLightMode();

    void btnClicked(const std::string& user);
public:
    explicit UsersWindow(QWidget *parent, Mode mode);

    void Load(const std::map<std::string, std::string>& users);
};

#endif //TCPCLIENT_USERSWINDOW_H