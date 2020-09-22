#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class downloader : public QObject
{
    Q_OBJECT
public:
    explicit downloader(QObject *parent = 0);

    QJsonDocument document;
    QJsonArray jsonArray;

signals:
    void onReady();

public slots:
    void getData();
    void onResult(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
};


#endif // DOWNLOADER_H
