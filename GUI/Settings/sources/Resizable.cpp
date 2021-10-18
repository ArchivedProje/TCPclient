// Copyright 2021 byteihq <kotov038@gmail.com>

#include <Resizable.h>

Resizable::Resizable(QWidget *parent, int width, int height) : QWidget(parent), width_(width), height_(height) {
    resize(width, height);
}

int Resizable::getWidth() const {
    return width_;
}

int Resizable::getHeight() const {
    return height_;
}

void Resizable::setResizable() {
    setMaximumSize(1920, 1080);
}

void Resizable::setUnResizable() {
    setFixedSize(width_, height_);
}
