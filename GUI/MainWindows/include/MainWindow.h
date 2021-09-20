

#ifndef TCPCLIENT_MAINWINDOW_H
#define TCPCLIENT_MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QMenuBar>
#include <QAction>
#include <ConnectWindow.h>
#include <GUISettingsWindow.h>

class MainWindow : public QMainWindow {
private:
    QStackedWidget *stackedWidgets_;
    ConnectWindow *connectWindow_;
    GUISettingsWindow *guiSettings_;
    QMenu *menuSettings_;
    QAction *actionGUI_;
    QAction *actionNetrok_;
    void setStyle(bool dark = true);
private slots:
    void showGUISettings();
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif //TCPCLIENT_MAINWINDOW_H
