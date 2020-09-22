#ifndef SCHEDULE_H
#define SCHEDULE_H

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
#include "playerstats.h"

class schedule : public QObject
{
    Q_OBJECT
public:
    explicit schedule(QObject *parent = nullptr);
    ~schedule();

    QJsonDocument document;
    QJsonArray jsonArray;
    QMultiMap<int, int> games;
    QMap<int, QString> date;

signals:
    void onReady();

public slots:
    void getData();
    void onResult(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    playerStats *playerStats;
};

#endif // SCHEDULE_H
