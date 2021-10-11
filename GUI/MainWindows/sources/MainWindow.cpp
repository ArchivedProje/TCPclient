// Copyright 2021 byteihq <kotov038@gmail.com>

#include <MainWindow.h>
#include <QPixmap>
#include <StyleSettings.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          thread_(std::make_unique<QThread>()),
                                          serverWindow_(std::make_unique<ServerWindow>(this)),
                                          stackedWidgets_(std::make_unique<QStackedWidget>(this)),
                                          connectWindow_(std::make_unique<ConnectWindow>(connection_, parent)),
                                          guiSettings_(std::make_unique<GUISettingsWindow>(parent)),
                                          networkSettings_(std::make_unique<NetworkSettingsWindow>(parent,
                                                                                                   guiSettings_->getMode())),
                                          menuSettings_(menuBar()->addMenu("Settings")),
                                          helpSettings_(menuBar()->addMenu("Help")),
                                          help_(std::make_unique<QAction>(QPixmap("img/questionIcon.png"), "Help",
                                                                          this)),
                                          aboutUs_(std::make_unique<QAction>("About us",
                                                                             this)),
                                          actionGUI_(std::make_unique<QAction>(
                                                  QPixmap("img/settingsGUIIcon.jpg"), "GUI",
                                                  this)),
                                          actionNetwork_(std::make_unique<QAction>(
                                                  QPixmap("img/settingsNetworkIcon.jpg"),
                                                  "Network",
                                                  this)) {
    if (guiSettings_->getMode() == Mode::Dark) {
        StyleSettings::setDarkMode(this);
    } else {
        StyleSettings::setLightMode(this);
    }

    resize(connectWindow_->getWidth(), connectWindow_->getHeight());

    connectWindow_->setIp(networkSettings_->getIp());
    connectWindow_->setPort(networkSettings_->getPort());

    helpSettings_->addAction(help_.get());
    helpSettings_->addSeparator();
    helpSettings_->addAction(aboutUs_.get());

    menuSettings_->addAction(actionGUI_.get());
    menuSettings_->addSeparator();
    menuSettings_->addAction(actionNetwork_.get());

    stackedWidgets_->addWidget(connectWindow_.get());
    stackedWidgets_->addWidget(serverWindow_.get());

    setCentralWidget(stackedWidgets_.get());

    stackedWidgets_->setCurrentIndex(0);

    connect(help_.get(), &QAction::triggered, this, &MainWindow::openDocUrl);

    connect(actionNetwork_.get(), &QAction::triggered, this, &MainWindow::showNetworkSettings);
    connect(actionGUI_.get(), &QAction::triggered, this, &MainWindow::showGUISettings);

    connect(guiSettings_.get(), &GUISettingsWindow::darkModeEnabled, this, &MainWindow::setDarkMode);
    connect(guiSettings_.get(), &GUISettingsWindow::lightModeEnabled, this, &MainWindow::setLightMode);

    connect(guiSettings_.get(), &GUISettingsWindow::darkModeEnabled, networkSettings_.get(),
            &NetworkSettingsWindow::setDarkMode);
    connect(guiSettings_.get(), &GUISettingsWindow::lightModeEnabled, networkSettings_.get(),
            &NetworkSettingsWindow::setLightMode);

    connect(this, &MainWindow::closeAllWindows, guiSettings_.get(), &GUISettingsWindow::close);
    connect(this, &MainWindow::closeAllWindows, networkSettings_.get(), &NetworkSettingsWindow::close);

    connect(connectWindow_.get(), &ConnectWindow::closeWindow, this, &MainWindow::exitBtnClicked);

    connect(connectWindow_.get(), &ConnectWindow::startListening, &connection_, &Connection::listen);
    connection_.moveToThread(thread_.get());
    thread_->start();
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

void MainWindow::showNetworkSettings() {
    networkSettings_->show();
}

void MainWindow::exitBtnClicked() {
    emit closeAllWindows();
    close();
}

void MainWindow::openDocUrl() {
    // open url
}
