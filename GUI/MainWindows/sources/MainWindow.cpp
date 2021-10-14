// Copyright 2021 byteihq <kotov038@gmail.com>

#include <MainWindow.h>
#include <QPixmap>
#include <StyleSettings.h>
#include <QDesktopServices>

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

    setMaximumSize(connectWindow_->getWidth(), connectWindow_->getHeight());

    stackedWidgets_->setCurrentIndex(0); // connectWindow

    connect(help_.get(), &QAction::triggered, this, &MainWindow::openDocUrl);
    connect(aboutUs_.get(), &QAction::triggered, this, &MainWindow::openAboutUsUrl);

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

    connect(connection_.handler_.get(), &RequestHandler::authorizeSucceed, this, &MainWindow::openServerWindow);

    connect(serverWindow_.get(), &ServerWindow::closeWindow, this, &MainWindow::exitBtnClicked);
    show();
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
    QDesktopServices::openUrl(QUrl("https://gist.github.com/byteihq/0ee5299bc54a874a3c468e32a47b082d", QUrl::TolerantMode));
}

void MainWindow::openAboutUsUrl() {
    QDesktopServices::openUrl(QUrl("https://gist.github.com/byteihq/1626637568a334dc7cfbe60bf4f4aa93", QUrl::TolerantMode));
}

void MainWindow::openServerWindow() {
    stackedWidgets_->setCurrentIndex(1); //serverWindow
    setMaximumSize(serverWindow_->getWidth(), serverWindow_->getHeight());
    resize(serverWindow_->getWidth(), serverWindow_->getHeight());
}
