// Copyright 2021 byteihq <kotov038@gmail.com>

#include <MainWindow.h>
#include <QPixmap>
#include <StyleSettings.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          stackedWidgets_(new QStackedWidget(this)),
                                          connectWindow_(new ConnectWindow(connection_, parent)),
                                          guiSettings_(new GUISettingsWindow(parent)),
                                          menuSettings_(menuBar()->addMenu("Settings")),
                                          actionGUI_(new QAction(
                                                  QPixmap("img/settingsGUIIcon.jpg"), "GUI",
                                                  this)),
                                          actionNetrok_(new QAction(
                                                  QPixmap("img/settingsNetworkIcon.jpg"),
                                                  "Network",
                                                  this)) {
    StyleSettings::setDarkMode(this);

    menuSettings_->addAction(actionGUI_);
    menuSettings_->addAction(actionNetrok_);

    stackedWidgets_->addWidget(connectWindow_);
    setCentralWidget(stackedWidgets_);
    show();
    stackedWidgets_->setCurrentIndex(0);

    connect(actionGUI_, &QAction::triggered, this, &MainWindow::showGUISettings);
    connect(guiSettings_, &GUISettingsWindow::darkModeEnabled, this, &MainWindow::setDarkMode);
    connect(guiSettings_, &GUISettingsWindow::lightModeEnabled, this, &MainWindow::setLightMode);
    connect(this, &MainWindow::closeAllWindows, guiSettings_, &GUISettingsWindow::close);

    connect(connectWindow_, &ConnectWindow::closeWindow, this, &MainWindow::exitBtnClicked);
}

void MainWindow::setDarkMode() {
    StyleSettings::setDarkMode(this);
}

void MainWindow::setLightMode() {
    StyleSettings::setLightMode(this);
}

void MainWindow::showGUISettings() {
    guiSettings_->show();
}

void MainWindow::exitBtnClicked() {
    emit closeAllWindows();
    close();
}

MainWindow::~MainWindow() {
    delete stackedWidgets_;
    delete connectWindow_;
    delete guiSettings_;
    delete menuSettings_;
    delete actionGUI_;
    delete actionNetrok_;
}
