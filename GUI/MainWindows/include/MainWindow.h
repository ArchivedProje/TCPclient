// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_MAINWINDOW_H
#define TCPCLIENT_MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QStackedWidget>
#include <QMenuBar>
#include <QAction>
#include <QThread>
#include <ConnectWindow.h>
#include <GUISettingsWindow.h>
#include <NetworkSettings.h>
#include <Connection.h>
#include <ServerWindow.h>
#include <UsersWindow.h>

class MainWindow : public QMainWindow {
Q_OBJECT
private:
    using upQM = std::unique_ptr<QMenu>;
    using upQA = std::unique_ptr<QAction>;

    std::shared_ptr<Connection> connection_;
    std::unique_ptr<QThread> thread_;
    std::unique_ptr<QStackedWidget> stackedWidgets_;
    std::unique_ptr<ConnectWindow> connectWindow_;
    std::unique_ptr<GUISettingsWindow> guiSettings_;
    std::unique_ptr<UsersWindow> usersWindow_;
    std::unique_ptr<NetworkSettingsWindow> networkSettings_;
    std::unique_ptr<ServerWindow> serverWindow_;
    upQM menuSettings_;
    upQA actionNetwork_;
    upQA actionGUI_;
    upQM helpSettings_;
    upQA actionHelp_;
    upQA actionAboutUs_;
    upQM serverSettings_;
    upQA actionUsers_;
    upQA actionDisconnect_;
    int currentIndex_;

    void updateWindow();

private slots:

    void setDarkMode();

    void setLightMode();

    void showGUISettings();

    void showNetworkSettings();

    void openDocUrl();

    void setResizable();

    void setUnResizable();

    void openServerWindow();

    void openAboutUsUrl();

    void showUsers(const Handler::StringMap& users);

    void exitBtnClicked();

public:
    explicit MainWindow(QWidget *parent = nullptr);
};

#endif //TCPCLIENT_MAINWINDOW_H
