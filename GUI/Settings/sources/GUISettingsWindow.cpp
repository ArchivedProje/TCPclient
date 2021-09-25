// Copyright 2021 byteihq <kotov038@gmail.com>

#include <GUISettingsWindow.h>
#include <StyleSettings.h>

GUISettingsWindow::GUISettingsWindow(QWidget *parent) : QWidget(parent), qvbox_(new QVBoxLayout(this)), darkModeQhbox_(new QHBoxLayout),
                                                        enableDarkMode_(new Switch()), enableDarkModeLabel_(new QLabel("Enable dark mode")) {

    StyleSettings::setDarkMode(this);

    setWindowTitle("GUI settings");

    enableDarkMode_->setLayoutDirection(Qt::RightToLeft);
    enableDarkMode_->setChecked(true);

    darkModeQhbox_->addWidget(enableDarkModeLabel_);
    darkModeQhbox_->addWidget(enableDarkMode_);

    qvbox_->addLayout(darkModeQhbox_);

    connect(enableDarkMode_, &Switch::stateChanged, this, &GUISettingsWindow::getCurrentModeState);
}

void GUISettingsWindow::getCurrentModeState(Qt::CheckState state) {
    if (state == Qt::Checked) {
        StyleSettings::setDarkMode(this);
        emit darkModeEnabled();
    } else {
        StyleSettings::setLightMode(this);
        emit lightModeEnabled();
    }
}

GUISettingsWindow::~GUISettingsWindow() {
    delete qvbox_;
    delete enableDarkMode_;
    delete enableDarkModeLabel_;
    delete darkModeQhbox_;
}
