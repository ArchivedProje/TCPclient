// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_CONNECTWINDOW_H
#define TCPCLIENT_CONNECTWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <Connection.h>

class ConnectWindow : public QWidget {
    Q_OBJECT
private:
    QHBoxLayout *qhbox_;
    QVBoxLayout *leftQvbox_;
    QVBoxLayout *rightQvbox_;
    QLabel *ipLabel_;
    QLabel *portLabel_;
    QLabel *loginLabel_;
    QLabel *passLabel_;
    QLineEdit *ipLine_;
    QLineEdit *portLine_;
    QLineEdit *loginLine_;
    QLineEdit *passLine_;
    QPushButton *connectBtn_;
    QPushButton *exitBtn_;

    Connection& connection_;
private slots:
    void exitBtnClicked();
    void connectBtnClicked();
signals:
    void closeWindow();
public:
    explicit ConnectWindow(Connection& connection, QWidget *parent);
    ~ConnectWindow();
};

#endif //TCPCLIENT_CONNECTWINDOW_H
