#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>
#include <QtDebug>
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


private slots:
    void on_buttonDownload_clicked();

private:
    Ui::Widget *ui;
    playerStats pS;
};
#endif // WIDGET_H
