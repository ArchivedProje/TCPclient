// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_RESIZABLE_H
#define TCPCLIENT_RESIZABLE_H

#include <QWidget>

class Resizable : public QWidget {
Q_OBJECT
private:
    int width_;
    int height_;
public:

    explicit Resizable(QWidget *parent, int width, int height);

    explicit Resizable(QWidget *parent);

    void setSize(int width, int height);

    void setWidth(int width);

    void setHeight(int height);

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

public slots:

    void setResizable();

    void setUnResizable();

};

#endif //TCPCLIENT_RESIZABLE_H
