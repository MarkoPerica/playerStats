#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QWidget>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>
#include <QtDebug>
#include <QTableWidgetItem>
#include <QPen>
#include <QBrush>
#include <QTextCharFormat>
#include "playerstats.h"
#include "downloader.h"
#include "schedule.h"
#include "playerstats.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void populateFirstColumn();
    void populateRest();
    void jsonReader();
    QString to_str(const QJsonValue& value, const std::string& name);
    double to_num(const QJsonValue& value, const std::string& name);
    QString per_game(const QJsonValue& value, const std::string&name, double games);
    QDate transformDate(const QString date);

public slots:
    void cellClicked(int iRow);

private slots:
    void on_buttonDownload_clicked();
    void readFile();

private:
    Ui::Widget *ui;
    playerStats *pS;
    downloader *downloader;
    schedule *schedule;
    QList<int> keys;


    QPen m_outlinePen;
    QBrush m_transparentBrush;
};
#endif // WIDGET_H
