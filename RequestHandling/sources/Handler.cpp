// Copyright 2021 byteihq <kotov038@gmail.com>

#include <Handler.h>
#include <QMessageBox>

void Handler::request(const std::string &request) {
    nlohmann::json jsonRequest = nlohmann::json::parse(request);
    if (jsonRequest["type"] == Requests::Auth) {
        if (jsonRequest["data"] == Replies::Auth::Successful) {
            emit authorizeSucceed();
        } else if (jsonRequest["data"] == Replies::Auth::Unsuccessful) {
            emit authorizeFailed();
        } else {
            emit unknownStatus();
        }
    } else if (jsonRequest["type"] == Requests::Msg) {
        if (jsonRequest["status"] == Status::Important && jsonRequest["sender"] == "server") {
            emit newMsg(QString::fromStdString(jsonRequest["sender"].get<std::string>()),
                        QString::fromStdString(jsonRequest["data"].get<std::string>()), "Important");
        } else {
            emit newMsg(QString::fromStdString(jsonRequest["sender"].get<std::string>()),
                        QString::fromStdString(jsonRequest["data"].get<std::string>()), "UnImportant");
        }
    } else if (jsonRequest["type"] == Requests::UserMsg) {
        emit newUserMsg(QString::fromStdString(jsonRequest["sender"].get<std::string>()),
                        QString::fromStdString(jsonRequest["data"].get<std::string>()));
    } else if (jsonRequest["type"] == Requests::GetUsers) {
        emit users(jsonRequest["data"].get<std::map<std::string, std::string>>());
    } else if (jsonRequest["type"] == Requests::ConnectToUser) {
        if (jsonRequest["data"] == Replies::ConnectToUser::Invite) {
            emit newInvite(QString::fromStdString(jsonRequest["sender"].get<std::string>()));
        } else if (jsonRequest["data"] == Replies::ConnectToUser::Accept) {
            emit startServer();
        } else if (jsonRequest["data"] == Replies::ConnectToUser::GetIp) {
            emit startClient(QString::fromStdString(jsonRequest["ip"].get<std::string>()));
        } else if (jsonRequest["data"] == Replies::ConnectToUser::Disconnected) {
            showErrMsg("This user disconnected");
        } else if (jsonRequest["data"] == Replies::ConnectToUser::Decline) {
            showErrMsg("This user declined your offer");
        }
    } else if (jsonRequest["type"] == Requests::Disconnect) {
        emit connectionAbort();
    } else if (jsonRequest["type"] == Requests::GetAllFiles) {
        if (jsonRequest["data"] == Replies::GetAllFiles::GetAllFiles) {
            emit sendAllFiles();
        } else if (jsonRequest["data"] == Replies::GetAllFiles::TakeAllFiles && jsonRequest["status"] != Replies::GetAllFiles::NoFiles) {
            QList<QString> paths;
            auto files = jsonRequest["files"].get<std::vector<std::string>>();
            for (const auto &item: files) {
                paths.push_back(QString::fromStdString(item));
            }
            emit setAllFiles(paths);
        }
    } else if (jsonRequest["type"] == Requests::GetFile) {
        if (jsonRequest["data"] == Replies::GetFile::GetFile) {
            emit sendFile(QString::fromStdString(jsonRequest["path"].get<std::string>()));
        } else if (jsonRequest["data"] == Replies::GetFile::TakeFile) {
            if (jsonRequest["status"] == Replies::GetFile::NoFile) {
                emit noFile(QString::fromStdString(jsonRequest["path"].get<std::string>()));
            } else if (jsonRequest["status"] == Replies::GetFile::FileExists) {
                emit setFile(QString::fromStdString(jsonRequest["name"].get<std::string>()), QString::fromStdString(jsonRequest["fileData"].get<std::string>()));
            }
        }
    }
}

nlohmann::json Handler::reply(const std::string &sender, const std::string &reply, Requests requestType) {
    nlohmann::json request = {
            {"sender", sender},
            {"type",   requestType},
            {"data",   reply}
    };
    return request;
}

void Handler::showErrMsg(const std::string &msg) {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Error");
    msgBox.setText(QString::fromStdString(msg));
    msgBox.exec();
}
