// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_NETWORKSETTINGS_H
#define TCPCLIENT_NETWORKSETTINGS_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include <string>
#include <memory>
#include <QGridLayout>
#include <StyleSettings.h>
#include <Resizable.h>

class MainWindow;

class NetworkSettingsWindow : public Resizable {
Q_OBJECT
private:
    friend class MainWindow;

    using upL = std::unique_ptr<QLabel>;
    using upLE = std::unique_ptr<QLineEdit>;
    using upPB = std::unique_ptr<QPushButton>;
    upL defIpLabel_;
    upLE defIpLineEdit_;
    upL defPortLabel_;
    std::unique_ptr<QSlider> defPortSlider_;
    std::unique_ptr<QSpinBox> defPortSpinBox_;
    upPB applyBtn_;
    upPB cancelBtn_;
    std::unique_ptr<QGridLayout> gridLayout_;
    std::string defIpValue_;
    int defPortValue_;

    void parseValues();

    [[nodiscard]] std::string getIp() const;

    [[nodiscard]] size_t getPort() const;
public slots:

    void setDarkMode();

    void setLightMode();

private slots:

    void applyBtnClicked();

    void ipUpdated();

    void portUpdated();

public:
    explicit NetworkSettingsWindow(QWidget *parent, Mode mode);
};

#endif //TCPCLIENT_NETWORKSETTINGS_H
