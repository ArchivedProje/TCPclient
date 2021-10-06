// Copyright 2021 byteihq <kotov038@gmail.com>

#include <GUISettingsWindow.h>
#include <fstream>
#include <ios>

GUISettingsWindow::GUISettingsWindow(QWidget *parent) : QWidget(parent),
                                                        gridLayout_(std::make_unique<QGridLayout>(this)),
                                                        enableDarkMode_(std::make_unique<Switch>()),
                                                        enableDarkModeLabel_(
                                                                std::make_unique<QLabel>("Enable dark mode")),
                                                        applyBtn_(std::make_unique<QPushButton>("Apply", this)),
                                                        cancelBtn_(std::make_unique<QPushButton>("Cancel", this)) {

    setWindowTitle("GUI settings");

    parseValues();

    enableDarkMode_->
            setLayoutDirection(Qt::RightToLeft);
    if (mode_ == Mode::Dark) {
        StyleSettings::setDarkMode(this);
        enableDarkMode_->setChecked(true);
    } else {
        StyleSettings::setLightMode(this);
        enableDarkMode_->setChecked(false);
    }

    gridLayout_->addWidget(enableDarkModeLabel_.get(), 0, 0);
    gridLayout_->addWidget(enableDarkMode_.get(), 0, 1);

    applyBtn_->setDisabled(true);
    applyBtn_->setStyleSheet("background-color: blue");
    gridLayout_->addWidget(applyBtn_.get(), 1, 0);
    gridLayout_->addWidget(cancelBtn_.get(), 1, 1);

    connect(enableDarkMode_.get(), &Switch::stateChanged,
            this, &GUISettingsWindow::getCurrentModeState);

    connect(cancelBtn_.get(), &QPushButton::clicked, this, &GUISettingsWindow::close);
    connect(applyBtn_.get(), &QPushButton::clicked, this, &GUISettingsWindow::applyBtnClicked);
}

void GUISettingsWindow::getCurrentModeState(Qt::CheckState state) {
    if (state == Qt::Checked) {
        StyleSettings::setDarkMode(this);
        emit darkModeEnabled();
        if (mode_ == Mode::Light) {
            applyBtn_->setEnabled(true);
        } else {
            applyBtn_->setDisabled(true);
        }
    } else {
        StyleSettings::setLightMode(this);
        emit lightModeEnabled();
        if (mode_ == Mode::Dark) {
            applyBtn_->setEnabled(true);
        } else {
            applyBtn_->setDisabled(true);
        }
    }
}

void GUISettingsWindow::parseValues() {
    std::ifstream cfgFile("Config/guiSettings.cfg", std::ios::in);
    std::string mode;
    cfgFile >> mode;
    mode_ = mode == "dark" ? Mode::Dark : Mode::Light;
    cfgFile.close();
}

void GUISettingsWindow::applyBtnClicked() {
    std::ofstream cfgFile("Config/guiSettings.cfg", std::ios::out);
    std::string mode = enableDarkMode_->checkState() == Qt::Checked ? "dark" : "light";
    cfgFile << mode;
    cfgFile.close();
}

Mode GUISettingsWindow::getMode() const {
    return mode_;
}
