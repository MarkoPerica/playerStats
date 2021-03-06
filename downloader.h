#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QFile>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <playerstats.h>

class downloader : public QObject
{
    Q_OBJECT
public:
    explicit downloader(QObject *parent = 0);
    ~downloader();

    QJsonDocument document;
    QJsonArray jsonArray;
    QMap<QString, int> players;

signals:
    void onReady();

public slots:
    void getData();
    void onResult(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    playerStats *playerStats;
};

#endif // DOWNLOADER_H
