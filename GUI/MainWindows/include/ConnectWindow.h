// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_CONNECTWINDOW_H
#define TCPCLIENT_CONNECTWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <memory>
#include <Connection.h>

class MainWindow;

class ConnectWindow : public QWidget {
Q_OBJECT
private:
    friend class MainWindow;

    using upL = std::unique_ptr<QLabel>;
    using upLE = std::unique_ptr<QLineEdit>;
    using upPB = std::unique_ptr<QPushButton>;
    upL ipLabel_;
    upL portLabel_;
    upL loginLabel_;
    upL passLabel_;
    upLE ipLine_;
    upLE portLine_;
    upLE loginLine_;
    upLE passLine_;
    upPB connectBtn_;
    upPB exitBtn_;

    std::unique_ptr<QGridLayout> gridLayout_;
    Connection& connection_;

    void setIp(const std::string &ip);

    void setPort(size_t port);

private slots:

    void exitBtnClicked();

    void connectBtnClicked();

    void showErrWindow(const std::string& errMsg);

    void showAuthFailed();

    void showUnStatus();
signals:

    void closeWindow();

    void startListening();

public:
    explicit ConnectWindow(Connection& connection, QWidget *parent);
};

#endif //TCPCLIENT_CONNECTWINDOW_H
