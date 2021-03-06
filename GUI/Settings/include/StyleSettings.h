// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_STYLESETTINGS_H
#define TCPCLIENT_STYLESETTINGS_H

#include <QWidget>

enum Mode {
    Dark,
    Light,
};

enum ResizeStatus {
    Resizable,
    UnResizable,
};

class StyleSettings {
public:
    static void setDarkMode(QWidget *window);

    static void setLightMode(QWidget *window);
};

#endif //TCPCLIENT_STYLESETTINGS_H
