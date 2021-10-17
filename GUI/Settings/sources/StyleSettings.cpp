// Copyright 2021 byteihq <kotov038@gmail.com>

#include <StyleSettings.h>
#include <QPalette>

void StyleSettings::setDarkMode(QWidget *window) {
    QPalette palette;

    palette.setColor(QPalette::Window, QColor(53, 53, 53));
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::ToolTipText, Qt::white);
    palette.setColor(QPalette::Base, QColor(73, 73, 73));
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::Button, QColor(53, 53, 53));
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::Highlight, QColor(103, 192, 252));
    palette.setColor(QPalette::HighlightedText, Qt::black);

    window->setPalette(palette);
}

void StyleSettings::setLightMode(QWidget *window) {
    QPalette palette;

    palette.setColor(QPalette::Window, QColor(230, 230, 230));
    palette.setColor(QPalette::WindowText, Qt::black);
    palette.setColor(QPalette::ToolTipText, Qt::black);
    palette.setColor(QPalette::Base, Qt::white);
    palette.setColor(QPalette::Text, Qt::black);
    palette.setColor(QPalette::Button, QColor(230, 230, 230));
    palette.setColor(QPalette::ButtonText, Qt::black);
    palette.setColor(QPalette::Highlight, QColor(103, 192, 252));
    palette.setColor(QPalette::HighlightedText, Qt::black);

    window->setPalette(palette);
}
