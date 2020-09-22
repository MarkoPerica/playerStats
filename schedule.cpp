#include "schedule.h"

schedule::schedule(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished, this, &schedule::onResult);

}

schedule::~schedule() {
    delete manager;
}

void schedule::getData() {
    QUrl url("https://api.sportsdata.io/v3/nba/scores/json/Games/2020?key=c48d9ff96d5b41708b8dca7a0b9c9667");
    QNetworkRequest request;
    request.setUrl(url);
    manager->get(request);
}

void schedule::onResult(QNetworkReply *reply) {
    if(reply->error()) {
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
    }
    else {
        document = QJsonDocument::fromJson(reply->readAll());
        jsonArray = document.array();
        int i = 0;
        foreach(const auto& value, jsonArray) {
            games.insert( i, value.toObject().value("HomeTeamID").toInt());
            games.insert( i, value.toObject().value("AwayTeamID").toInt());
            date.insert( i, value.toObject().value("Date").toString());
            i++;
        }
    }
    qDebug() << "Download completed";
    reply->deleteLater();
    emit onReady();
}
