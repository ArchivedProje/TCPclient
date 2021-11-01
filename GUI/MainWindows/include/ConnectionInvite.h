//

#ifndef TCPCLIENT_CONNECTIONINVITE_H
#define TCPCLIENT_CONNECTIONINVITE_H

#include <Resizable.h>
#include <StyleSettings.h>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <memory>
#include <string>

class MainWindow;

class ConnectionInvite : public Resizable {
private:
    friend class MainWindow;

    std::unique_ptr<QGridLayout> qgrid_;
    std::unique_ptr<QLabel> qlabel_;
    using upPB = std::unique_ptr<QPushButton>;
    upPB acceptBtn_;
    upPB declineBtn_;

private slots:

    void setDarkMode();

    void setLightMode();

    void newInvite(const std::string &userName);

public:
    explicit ConnectionInvite(QWidget *parent, Mode mode);
};

#endif //TCPCLIENT_CONNECTIONINVITE_H
