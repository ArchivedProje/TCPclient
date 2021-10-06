// Copyright 2021 byteihq <kotov038@gmail.com>

#include <NetworkSettings.h>
#include <StyleSettings.h>
#include <QString>
#include <fstream>
#include <ios>
#include <boost/asio.hpp>

NetworkSettingsWindow::NetworkSettingsWindow(QWidget *parent) : QWidget(parent),
                                                                qhbox_(std::make_unique<QHBoxLayout>(this)),
                                                                leftQvbox_(std::make_unique<QVBoxLayout>()),
                                                                rightQVbox_(std::make_unique<QVBoxLayout>()),
                                                                defIpLabel_(
                                                                        std::make_unique<QLabel>("Default IP", this)),
                                                                defIpLineEdit_(std::make_unique<QLineEdit>()),
                                                                defPortLabel_(
                                                                        std::make_unique<QLabel>("Default port", this)),
                                                                defPortSlider_(std::make_unique<QSlider>(Qt::Horizontal,
                                                                                                         this)),
                                                                defPortSpinBox_(std::make_unique<QSpinBox>(this)),
                                                                rightPortPart_(std::make_unique<QHBoxLayout>()),
                                                                applyBtn_(std::make_unique<QPushButton>("Apply", this)),
                                                                cancelBtn_(
                                                                        std::make_unique<QPushButton>("Cancel", this)) {
    StyleSettings::setDarkMode(this);

    parseValues();

    leftQvbox_->addWidget(defIpLabel_.get());

    defIpLineEdit_->setText(QString::fromStdString(defIpValue_));
    rightQVbox_->addWidget(defIpLineEdit_.get());

    defPortSlider_->setMinimum(1);
    defPortSlider_->setMaximum(65536);
    defPortSlider_->setValue(defPortValue_);
    defPortSpinBox_->setMinimum(1);
    defPortSpinBox_->setMaximum(65536);
    defPortSpinBox_->setValue(defPortValue_);
    rightPortPart_->addWidget(defPortSlider_.get());
    rightPortPart_->addWidget(defPortSpinBox_.get());

    leftQvbox_->addWidget(defPortLabel_.get());
    rightQVbox_->addLayout(rightPortPart_.get());

    applyBtn_->setDisabled(true);
    applyBtn_->setStyleSheet("background-color: blue");
    leftQvbox_->addWidget(applyBtn_.get());
    rightQVbox_->addWidget(cancelBtn_.get());

    qhbox_->addLayout(leftQvbox_.get());
    qhbox_->addLayout(rightQVbox_.get());

    connect(cancelBtn_.get(), &QPushButton::clicked, this, &NetworkSettingsWindow::close);
    connect(applyBtn_.get(), &QPushButton::clicked, this, &NetworkSettingsWindow::applyBtnClicked);

    connect(defIpLineEdit_.get(), &QLineEdit::textChanged, this, &NetworkSettingsWindow::ipUpdated);

    connect(defPortSlider_.get(), &QSlider::valueChanged, defPortSpinBox_.get(), &QSpinBox::setValue);
    connect(defPortSlider_.get(), &QSlider::valueChanged, this, &NetworkSettingsWindow::portUpdated);

    connect(defPortSpinBox_.get(), SIGNAL(valueChanged(int)), defPortSlider_.get(), SLOT(setValue(int)));
    connect(defPortSpinBox_.get(), SIGNAL(valueChanged(int)), this, SLOT(portUpdated()));

}

void NetworkSettingsWindow::parseValues() {
    std::ifstream cfgFile("Config/settings.cfg", std::ios::in);
    cfgFile >> defIpValue_ >> defPortValue_;
    cfgFile.close();
}

void NetworkSettingsWindow::setDarkMode() {
    StyleSettings::setDarkMode(this);
}

void NetworkSettingsWindow::setLightMode() {
    StyleSettings::setLightMode(this);
}

void NetworkSettingsWindow::ipUpdated() {
    boost::system::error_code ec;
    auto ip = boost::asio::ip::address::from_string(defIpLineEdit_->text().toStdString(), ec);
    if (ec) {
        defIpLineEdit_->setStyleSheet("background-color: red");
        applyBtn_->setDisabled(true);
    } else {
        defIpLineEdit_->setStyleSheet("background-color: white");
        if (defIpLineEdit_->text().toStdString() != defIpValue_) {
            applyBtn_->setEnabled(true);
        } else {
            applyBtn_->setDisabled(true);
        }
    }
}

void NetworkSettingsWindow::portUpdated() {
    if (defPortSlider_->value() != defPortValue_) {
        applyBtn_->setEnabled(true);
    } else {
        applyBtn_->setDisabled(true);
    }
}

void NetworkSettingsWindow::applyBtnClicked() {
    applyBtn_->setDisabled(true);
    std::ofstream cfgFile("Config/settings.cfg", std::ios::out);
    cfgFile << defIpLineEdit_->text().toStdString() << std::endl << defPortSlider_->value();
    cfgFile.close();
}
