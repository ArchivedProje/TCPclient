// Copyright 2021 byteihq <kotov038@gmail.com>

#include <GUISettingsWindow.h>
#include <StyleSettings.h>

GUISettingsWindow::GUISettingsWindow(QWidget *parent) : QWidget(parent), gridLayout_(std::make_unique<QGridLayout>(this)),
                                                        enableDarkMode_(std::make_unique<Switch>()),
                                                        enableDarkModeLabel_(
                                                                std::make_unique<QLabel>("Enable dark mode")) {

    StyleSettings::setDarkMode(this);

    setWindowTitle("GUI settings");

    enableDarkMode_->
            setLayoutDirection(Qt::RightToLeft);
    enableDarkMode_->setChecked(true);

    gridLayout_->addWidget(enableDarkModeLabel_.get(), 0, 0);
    gridLayout_->addWidget(enableDarkMode_.get(), 0, 1);

    connect(enableDarkMode_.get(), &Switch::stateChanged,
            this, &GUISettingsWindow::getCurrentModeState);
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
