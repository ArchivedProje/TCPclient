// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPCLIENT_FILESETTINGS_H
#define TCPCLIENT_FILESETTINGS_H

#include <Resizable.h>
#include <StyleSettings.h>
#include <QGridLayout>
#include <QFileSystemModel>
#include <QModelIndex>
#include <QListView>
#include <QListWidget>
#include <QPushButton>
#include <vector>
#include <boost/filesystem.hpp>
#include <memory>

class MainWindow;

class FileSettings : public Resizable {
    Q_OBJECT
private:
    friend class MainWindow;
    std::unique_ptr<QGridLayout> qgrid_;
    std::unique_ptr<QFileSystemModel> model_;
    std::unique_ptr<QListView> leftView_;
    std::unique_ptr<QListWidget> rightView_;
    using upQP = std::unique_ptr<QPushButton>;
    upQP appendBtn_;
    upQP deleteBtn_;
    upQP applyBtn_;
    upQP closeBtn_;
    std::vector<boost::filesystem::path> files_;

    void parseFiles();

    void setData();

private slots:
    void doubleClick(const QModelIndex& index);

    void appendBtnClicked();

    void deleteBtnClicked();

    void applyBtnClicked();

    void setDarkMode();

    void setLightMode();
public:
    explicit FileSettings(QWidget *parent, Mode mode);

    static std::vector<std::string> getFiles();
};

#endif //TCPCLIENT_FILESETTINGS_H
