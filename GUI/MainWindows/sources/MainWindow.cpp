
#include <MainWindow.h>
#include <QPalette>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), stackedWidgets_(new QStackedWidget(this)),
                                          connectWindow_(new ConnectWindow(parent)),
                                          guiSettings_(new GUISettingsWindow(parent)),
                                          menuSettings_(menuBar()->addMenu("Settings")),
                                          actionGUI_(new QAction(QPixmap("img/settingsGUIIcon.jpg"), "GUI", this)),
                                          actionNetrok_(new QAction(QPixmap("img/settingsNetworkIcon.jpg"), "Network",
                                                                    this)) {
    setStyle(false);

    menuSettings_->addAction(actionGUI_);
    menuSettings_->addAction(actionNetrok_);

    stackedWidgets_->addWidget(connectWindow_);
    setCentralWidget(stackedWidgets_);
    show();
    stackedWidgets_->setCurrentIndex(0);

    connect(actionGUI_, &QAction::triggered, this, &MainWindow::showGUISettings);
}

void MainWindow::setStyle(bool dark) {
    QPalette palette;
    if (dark) {
        palette.setColor(QPalette::Window, QColor(53, 53, 53));
        palette.setColor(QPalette::WindowText, Qt::white);
        palette.setColor(QPalette::ToolTipText, Qt::white);
        palette.setColor(QPalette::Text, Qt::black);
        palette.setColor(QPalette::Button, QColor(53, 53, 53));
        palette.setColor(QPalette::ButtonText, Qt::white);
        palette.setColor(QPalette::Highlight, QColor(103, 192, 252));
        palette.setColor(QPalette::HighlightedText, Qt::black);
    } else {
        palette.setColor(QPalette::Window, QColor(230, 230, 230));
        palette.setColor(QPalette::WindowText, Qt::black);
        palette.setColor(QPalette::ToolTipText, Qt::black);
        palette.setColor(QPalette::Text, Qt::black);
        palette.setColor(QPalette::Button, QColor(230, 230, 230));
        palette.setColor(QPalette::ButtonText, Qt::black);
        palette.setColor(QPalette::Highlight, QColor(103, 192, 252));
        palette.setColor(QPalette::HighlightedText, Qt::black);
    }
    setPalette(palette);
}

void MainWindow::showGUISettings() {
    guiSettings_->show();
}

MainWindow::~MainWindow() {
    delete stackedWidgets_;
    delete connectWindow_;
    delete guiSettings_;
    delete menuSettings_;
    delete actionGUI_;
    delete actionNetrok_;
}
