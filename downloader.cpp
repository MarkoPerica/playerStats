#include "downloader.h"

downloader::downloader(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished, this, &downloader::onResult);
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
        QFile *file = new QFile("C:/temp/players.json");
        if (file->open(QFile::WriteOnly)) {
            file->write(reply->readAll());
            file->close();
        }
    }
    qDebug() << "Download completed";
    emit onReady();
}
