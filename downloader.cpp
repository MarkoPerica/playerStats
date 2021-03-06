#include "downloader.h"

downloader::downloader(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished, this, &downloader::onResult);
}

downloader::~downloader() {
    delete manager;
}

void downloader::getData() {
    QUrl url("https://api.sportsdata.io/v3/nba/stats/json/PlayerSeasonStats/2020?key=c48d9ff96d5b41708b8dca7a0b9c9667");
    QNetworkRequest request;
    request.setUrl(url);
    manager->get(request);
}

void downloader::onResult(QNetworkReply *reply) {
    if(reply->error()) {
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
    }
    else {
        document = QJsonDocument::fromJson(reply->readAll());
        jsonArray = document.array();
        foreach(auto && value, jsonArray) {
            players.insert(value.toObject().value("Name").toString(), value.toObject().value("TeamID").toInt());
        }
    }
    qDebug() << "Download completed";
    reply->deleteLater();
    emit onReady();
}
