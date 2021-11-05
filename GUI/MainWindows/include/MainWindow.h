// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_MAINWINDOW_H
#define TCPCLIENT_MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QStackedWidget>
#include <QMenuBar>
#include <QAction>
#include <QThread>
#include <ServerConnection.h>
#include <ConnectWindow.h>
#include <GUISettingsWindow.h>
#include <NetworkSettings.h>
#include <ServerConnection.h>
#include <ServerWindow.h>
#include <FileSettings.h>
#include <ConnectionInvite.h>
#include <UsersWindow.h>
#include <UserConversation.h>


class MainWindow : public QMainWindow {
Q_OBJECT
private:
    using upQM = std::unique_ptr<QMenu>;
    using upQA = std::unique_ptr<QAction>;

    std::shared_ptr<ServerConnection> connection_;
    std::unique_ptr<QThread> thread_;
    std::shared_ptr<QThread> clientThread_;
    std::shared_ptr<QThread> serverThread_;
    std::unique_ptr<QStackedWidget> stackedWidgets_;
    std::unique_ptr<ConnectWindow> connectWindow_;
    std::unique_ptr<GUISettingsWindow> guiSettings_;
    std::unique_ptr<UserConversation> userConversation_;
    std::unique_ptr<ConnectionInvite> connectionInvite_;
    std::unique_ptr<NetworkSettingsWindow> networkSettings_;
    std::unique_ptr<ServerWindow> serverWindow_;
    std::unique_ptr<UsersWindow> usersWindow_;
    std::unique_ptr<FileSettings> fileSettings_;
    upQM menuSettings_;
    upQA actionNetwork_;
    upQA actionGUI_;
    upQA actionFile_;
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
    explicit MainWindow(std::shared_ptr<boost::asio::io_service>& ioService_, QWidget *parent = nullptr);
};

#endif //TCPCLIENT_MAINWINDOW_H
