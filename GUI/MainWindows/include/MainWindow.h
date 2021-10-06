// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_MAINWINDOW_H
#define TCPCLIENT_MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QStackedWidget>
#include <QMenuBar>
#include <QAction>
#include <ConnectWindow.h>
#include <GUISettingsWindow.h>
#include <NetworkSettings.h>
#include <Connection.h>

class MainWindow : public QMainWindow {
Q_OBJECT
private:
    std::unique_ptr<QStackedWidget> stackedWidgets_;
    std::unique_ptr<ConnectWindow> connectWindow_;
    std::unique_ptr<GUISettingsWindow> guiSettings_;
    std::unique_ptr<NetworkSettingsWindow> networkSettings_;
    std::unique_ptr<QMenu> menuSettings_;
    std::unique_ptr<QAction> actionGUI_;
    std::unique_ptr<QAction> actionNetwork_;

    Connection connection_;
signals:

    void closeAllWindows();

private slots:

    void setDarkMode();

    void setLightMode();

    void showGUISettings();

    void showNetworkSettings();

    void exitBtnClicked();

public:
    explicit MainWindow(QWidget *parent = nullptr);
};

#endif //TCPCLIENT_MAINWINDOW_H
