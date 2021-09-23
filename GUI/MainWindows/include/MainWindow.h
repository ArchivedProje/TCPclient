// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_MAINWINDOW_H
#define TCPCLIENT_MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QMenuBar>
#include <QAction>
#include <ConnectWindow.h>
#include <GUISettingsWindow.h>
#include <Connection.h>

class MainWindow : public QMainWindow {
private:
    QStackedWidget *stackedWidgets_;
    ConnectWindow *connectWindow_;
    GUISettingsWindow *guiSettings_;
    QMenu *menuSettings_;
    QAction *actionGUI_;
    QAction *actionNetrok_;

    Connection& connection_;
private slots:
    void setDarkMode();
    void setLightMode();
    void showGUISettings();
public:
    explicit MainWindow(Connection& connection, QWidget *parent = nullptr);
    ~MainWindow();
};

#endif //TCPCLIENT_MAINWINDOW_H
