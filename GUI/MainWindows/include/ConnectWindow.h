
#ifndef TCPCLIENT_CONNECTWINDOW_H
#define TCPCLIENT_CONNECTWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class ConnectWindow : public QWidget {
private:
    QVBoxLayout *qvbox_;
    QHBoxLayout *qhboxIp_;
    QHBoxLayout *qhboxLogin_;
    QHBoxLayout *qhboxPass_;
    QHBoxLayout *qhboxButtons_;
    QLabel *ipLabel_;
    QLabel *loginLabel_;
    QLabel *passLabel_;
    QLineEdit *ipLine_;
    QLineEdit *loginLine_;
    QLineEdit *passLine_;
    QPushButton *connectBtn_;
    QPushButton *exitBtn_;
public:
    explicit ConnectWindow(QWidget *parent);
    ~ConnectWindow();
};

#endif //TCPCLIENT_CONNECTWINDOW_H
