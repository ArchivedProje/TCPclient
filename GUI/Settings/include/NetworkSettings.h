// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_NETWORKSETTINGS_H
#define TCPCLIENT_NETWORKSETTINGS_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <string>
#include <memory>
#include <StyleSettings.h>

class NetworkSettingsWindow : public QWidget {
Q_OBJECT
private:
    using upQH = std::unique_ptr<QHBoxLayout>;
    using upQV = std::unique_ptr<QVBoxLayout>;
    using upL = std::unique_ptr<QLabel>;
    using upLE = std::unique_ptr<QLineEdit>;
    using upPB = std::unique_ptr<QPushButton>;

    upQH qhbox_;
    upQV leftQvbox_;
    upQV rightQVbox_;
    upL defIpLabel_;
    upLE defIpLineEdit_;
    upL defPortLabel_;
    std::unique_ptr<QSlider> defPortSlider_;
    std::unique_ptr<QSpinBox> defPortSpinBox_;
    upQH rightPortPart_;
    upPB applyBtn_;
    upPB cancelBtn_;

    std::string defIpValue_;
    int defPortValue_;

    void parseValues();

public slots:

    void setDarkMode();

    void setLightMode();

private slots:

    void applyBtnClicked();

    void ipUpdated();

    void portUpdated();

public:
    explicit NetworkSettingsWindow(QWidget *parent);
};

#endif //TCPCLIENT_NETWORKSETTINGS_H
