#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_buttonDownload_clicked()
{
    QFile file;
    QVariantMap map;
    file.setFileName("players.json");
    if (!file.open((QIODevice::ReadOnly|QIODevice::Text))) {
        QMessageBox::critical(0, "Error", "Failed to open\n");
    }
    QTextStream file_text(&file);
    QString json_string;
    json_string = file_text.readAll();
    file.close();
    QByteArray json_bytes = json_string.toLocal8Bit();

    auto json_doc = QJsonDocument::fromJson(json_bytes);

    if (json_doc.isNull()) {
        QMessageBox::critical(0, "Error", "Failed to create JSON doc\n");
    }

    QJsonObject object = json_doc.object();

    QJsonValue value = object.value("playersArray");
    QJsonArray array = value.toArray();

}
