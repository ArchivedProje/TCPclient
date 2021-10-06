// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_GUISETTINGSWINDOW_H
#define TCPCLIENT_GUISETTINGSWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <memory>
#include <string>
#include <switch.h>
#include <StyleSettings.h>

class GUISettingsWindow : public QWidget {
Q_OBJECT
private:
    std::unique_ptr<QGridLayout> gridLayout_;
    std::unique_ptr<Switch> enableDarkMode_;
    std::unique_ptr<QLabel> enableDarkModeLabel_;
    std::unique_ptr<QPushButton> applyBtn_;
    std::unique_ptr<QPushButton> cancelBtn_;

    Mode mode_;

    void parseValues();

private slots:

    void getCurrentModeState(Qt::CheckState state);

    void applyBtnClicked();

signals:

    void lightModeEnabled();

    void darkModeEnabled();

public:
    explicit GUISettingsWindow(QWidget *parent);

    Mode getMode() const;
};

#endif //TCPCLIENT_GUISETTINGSWINDOW_H
