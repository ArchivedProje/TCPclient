// Copyright 2021 byteihq <kotov038@gmail.com>

#include <GUISettingsWindow.h>
#include <fstream>
#include <ios>

GUISettingsWindow::GUISettingsWindow(QWidget *parent) : Resizable(parent, 268, 131),
                                                        gridLayout_(std::make_unique<QGridLayout>(this)),
                                                        enableDarkModeSwitch_(std::make_unique<Switch>()),
                                                        enableDarkModeLabel_(
                                                                std::make_unique<QLabel>("Enable dark mode")),
                                                        resizableLabel_(
                                                                std::make_unique<QLabel>("Enable window resizing")),
                                                        resizableSwitch_(std::make_unique<Switch>()),
                                                        applyBtn_(std::make_unique<QPushButton>("Apply", this)),
                                                        cancelBtn_(std::make_unique<QPushButton>("Close", this)) {

    setWindowTitle("GUI settings");

    parseValues();

    enableDarkModeSwitch_->
            setLayoutDirection(Qt::RightToLeft);
    resizableSwitch_->setLayoutDirection(Qt::RightToLeft);

    if (mode_ == Mode::Dark) {
        StyleSettings::setDarkMode(this);
        enableDarkModeSwitch_->setChecked(true);
    } else {
        StyleSettings::setLightMode(this);
        enableDarkModeSwitch_->setChecked(false);
    }

    if (resizable_ == ResizeStatus::False) {
        resizableSwitch_->setChecked(false);
        setUnResizable();
    } else {
        resizableSwitch_->setChecked(true);
    }

    gridLayout_->addWidget(enableDarkModeLabel_.get(), 0, 0);
    gridLayout_->addWidget(enableDarkModeSwitch_.get(), 0, 1);
    gridLayout_->addWidget(resizableLabel_.get(), 1, 0);
    gridLayout_->addWidget(resizableSwitch_.get(), 1, 1);

    applyBtn_->setDisabled(true);
    applyBtn_->setStyleSheet("background-color: blue");
    gridLayout_->addWidget(applyBtn_.get(), 2, 0);
    gridLayout_->addWidget(cancelBtn_.get(), 2, 1);

    connect(enableDarkModeSwitch_.get(), &Switch::stateChanged,
            this, &GUISettingsWindow::getCurrentModeState);
    connect(resizableSwitch_.get(), &Switch::stateChanged, this, &GUISettingsWindow::getCurrentResizableState);

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

void GUISettingsWindow::getCurrentResizableState(Qt::CheckState state) {
    if (state == Qt::Checked) {
        setResizable();
        emit resizable();
        if (resizable_ == ResizeStatus::False) {
            applyBtn_->setEnabled(true);
        } else {
            applyBtn_->setDisabled(true);
        }
    } else {
        setUnResizable();
        emit unresizable();
        if (resizable_ == ResizeStatus::True) {
            applyBtn_->setEnabled(true);
        } else {
            applyBtn_->setDisabled(true);
        }
    }
}

void GUISettingsWindow::parseValues() {
    std::ifstream cfgFile("Config/guiSettings.cfg", std::ios::in);
    std::string mode;
    std::string resizable;
    cfgFile >> mode >> resizable;
    mode_ = mode == "dark" ? Mode::Dark : Mode::Light;
    resizable_ = resizable == "true" ? ResizeStatus::True : ResizeStatus::False;
    cfgFile.close();
}

void GUISettingsWindow::applyBtnClicked() {
    applyBtn_->setDisabled(true);
    std::ofstream cfgFile("Config/guiSettings.cfg", std::ios::out);
    std::string mode = enableDarkModeSwitch_->checkState() == Qt::Checked ? "dark" : "light";
    std::string resizable = resizableSwitch_->checkState() == Qt::Checked ? "true" : "false";
    cfgFile << mode << std::endl << resizable;
    cfgFile.close();
}

Mode GUISettingsWindow::getMode() const {
    return mode_;
}

ResizeStatus GUISettingsWindow::getResizable() const {
    return resizable_;
}
