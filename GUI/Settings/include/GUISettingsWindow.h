// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_GUISETTINGSWINDOW_H
#define TCPCLIENT_GUISETTINGSWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <memory>
#include <switch.h>

class GUISettingsWindow : public QWidget {
    Q_OBJECT
private:
    std::unique_ptr<QGridLayout> gridLayout_;
    std::unique_ptr<Switch> enableDarkMode_;
    std::unique_ptr<QLabel> enableDarkModeLabel_;
private slots:
    void getCurrentModeState(Qt::CheckState state);
signals:
    void lightModeEnabled();
    void darkModeEnabled();
public:
    explicit GUISettingsWindow(QWidget *parent);
};

#endif //TCPCLIENT_GUISETTINGSWINDOW_H
