
#ifndef TCPCLIENT_GUISETTINGSWINDOW_H
#define TCPCLIENT_GUISETTINGSWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <switch.h>

class GUISettingsWindow : public QWidget {
public:
    QVBoxLayout *qvbox_;
    Switch *enableDarkMode_;
public:
    explicit GUISettingsWindow(QWidget *parent);
    ~GUISettingsWindow();
};

#endif //TCPCLIENT_GUISETTINGSWINDOW_H
