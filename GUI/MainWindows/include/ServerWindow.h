// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_SERVERWINDOW_H
#define TCPCLIENT_SERVERWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <memory>
#include <Connection.h>

class MainWindow;

class ServerWindow : public QWidget {
    Q_OBJECT
private:
    friend class MainWindow;

    using upPB = std::unique_ptr<QPushButton>;

    std::unique_ptr<QGridLayout> gridLayout_;
    std::unique_ptr<QListWidget> infoWidget_;
    std::unique_ptr<QLineEdit> lineEdit_;
    upPB sendBtn_;
    upPB usersBtn_;
    upPB statBtn_;
    upPB exitBtn_;

    size_t height_;
    size_t width_;
private slots:
    void exitBtnClicked();

signals:
    void closeWindow();
public:
    explicit ServerWindow(QWidget *parent);

    size_t getHeight() const;

    size_t getWidth() const;
};

#endif //TCPCLIENT_SERVERWINDOW_H
