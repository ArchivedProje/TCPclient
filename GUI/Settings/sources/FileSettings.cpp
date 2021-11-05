// Copyright 2021 byteihq <kotov038@gmail.com>

#include <FileSettings.h>
#include <QDir>
#include <fstream>
#include <ios>
#include <algorithm>

FileSettings::FileSettings(QWidget *parent, Mode mode) : Resizable(parent, 600, 300),
                                                         qgrid_(std::make_unique<QGridLayout>(this)),
                                                         model_(std::make_unique<QFileSystemModel>()),
                                                         leftView_(std::make_unique<QListView>()),
                                                         rightView_(std::make_unique<QListWidget>()),
                                                         appendBtn_(std::make_unique<QPushButton>("Append ->", this)),
                                                         deleteBtn_(std::make_unique<QPushButton>("<- Delete", this)),
                                                         applyBtn_(std::make_unique<QPushButton>("Apply", this)),
                                                         closeBtn_(std::make_unique<QPushButton>("Close", this)) {

    parseFiles();
    setData();

    if (mode == Mode::Dark) {
        StyleSettings::setDarkMode(this);
    } else {
        StyleSettings::setLightMode(this);
    }

    model_->setFilter(QDir::QDir::AllEntries);
    model_->setRootPath("");
    leftView_->setModel(model_.get());

    qgrid_->addWidget(leftView_.get(), 0, 0, 6, 1);
    qgrid_->addWidget(rightView_.get(), 0, 2, 6, 1);

    qgrid_->addWidget(appendBtn_.get(), 1, 1);
    qgrid_->addWidget(deleteBtn_.get(), 2, 1);

    applyBtn_->setDisabled(true);
    applyBtn_->setStyleSheet("background-color: blue");
    qgrid_->addWidget(applyBtn_.get(), 4, 1);
    qgrid_->addWidget(closeBtn_.get(), 5, 1);
    connect(leftView_.get(), &QListView::doubleClicked, this, &FileSettings::doubleClick);
    connect(appendBtn_.get(), &QPushButton::clicked, this, &FileSettings::appendBtnClicked);
    connect(deleteBtn_.get(), &QPushButton::clicked, this, &FileSettings::deleteBtnClicked);
    connect(applyBtn_.get(), &QPushButton::clicked, this, &FileSettings::applyBtnClicked);
    connect(closeBtn_.get(), &QPushButton::clicked, this, &FileSettings::close);
}

void FileSettings::doubleClick(const QModelIndex &index) {
    auto file = model_->fileInfo(index);
    if (file.fileName() == "..") {
        auto dirUp = file.dir();
        dirUp.cdUp();
        leftView_->setRootIndex(model_->index(dirUp.absolutePath()));
    } else if (file.fileName() == ".") {
        leftView_->setRootIndex(model_->index(""));
    } else if (file.isDir()) {
        leftView_->setRootIndex(index);
    }
}

void FileSettings::appendBtnClicked() {
    auto selectedItems = leftView_->selectionModel()->selectedIndexes();
    for (const auto &item: selectedItems) {
        if (model_->fileInfo(item).isFile()) {
            QString Qpath = model_->fileName(item) + " (" + model_->fileInfo(item).absolutePath() + '/' +
                            model_->fileName(item) + ")";
            rightView_->addItem(Qpath);
            std::string path = Qpath.toStdString();
            path = std::string(path.begin() + path.find(' ') + 2, path.end() - 1);
            files_.emplace_back(std::move(path));
        }
    }
    applyBtn_->setEnabled(true);
}

void FileSettings::deleteBtnClicked() {
    auto items = rightView_->selectedItems();
    for (const auto &item: items) {
        std::string path = item->text().toStdString();
        path = std::string(path.begin() + path.find(' ') + 2, path.end() - 1);
        files_.erase(std::find(files_.begin(), files_.end(), path));
    }
    qDeleteAll(items);
    applyBtn_->setEnabled(true);
}

void FileSettings::setDarkMode() {
    StyleSettings::setDarkMode(this);
}

void FileSettings::setLightMode() {
    StyleSettings::setLightMode(this);
}

void FileSettings::parseFiles() {
    std::ifstream in("Config/fileSettings.cfg", std::ios::in);
    std::string path;
    while (std::getline(in, path)) {
        if (!path.empty()) {
            files_.emplace_back(std::next(path.begin()), std::prev(path.end()));
        }
    }
}

void FileSettings::setData() {
    for (const auto &path: files_) {
        std::string fullPath = path.filename().string() + " (" + path.string() + ")";
        rightView_->addItem(QString::fromStdString(fullPath));
    }
}

void FileSettings::applyBtnClicked() {
    std::ofstream out("Config/fileSettings.cfg", std::ios::out);
    bool first = true;
    for (const auto &path: files_) {
        if (!first) {
            out << std::endl;
        }
        out << path;
        first = false;
    }
    applyBtn_->setDisabled(true);
}

std::vector<std::string> FileSettings::getFiles() {
    std::ifstream in("Config/fileSettings.cfg", std::ios::in);
    std::string path;
    std::getline(in, path);
    std::vector<std::string> res;
    while (std::getline(in, path)) {
        if (!path.empty()) {
            res.emplace_back(std::next(path.begin()), std::prev(path.end()));
        }
    }
    return res;
}
