// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_GUISETTINGSWINDOW_H
#define TCPCLIENT_GUISETTINGSWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <switch.h>

class GUISettingsWindow : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout *qvbox_;
    QHBoxLayout *darkModeQhbox_;
    Switch *enableDarkMode_;
    QLabel *enableDarkModeLabel_;
private slots:
    void getCurrentModeState(Qt::CheckState state);
signals:
    void lightModeEnabled();
    void darkModeEnabled();
public:
    explicit GUISettingsWindow(QWidget *parent);
    ~GUISettingsWindow();
};

#endif //TCPCLIENT_GUISETTINGSWINDOW_H
