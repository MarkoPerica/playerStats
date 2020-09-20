#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QStringList header;
    header << "Name" << "Games" << "Rebounds" << "Assists" << "Steals" << "Blocks" << "Points" << "Fantasy Points";
    setWindowTitle("Player Stats");
    ui->playerTable->setColumnCount(8);
    ui->playerTable->setHorizontalHeaderLabels(header);
    ui->playerTable->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::populateFirstColumn()
{
    int j;
    QMap<int, QString>::iterator i;
    for(i = pS._name.begin(), j = 0; i != pS._name.end(); i++, j++) {
        ui->playerTable->setRowCount(j+1);
        auto *pCell = new QTableWidgetItem(i.value());
        ui->playerTable->setItem(j, 0, pCell);
    }
}

void Widget::populateRest() {
    int j = 0, k;
    QMap<int, double>::iterator i;
        for (i = pS._stats.begin(), k = 1; i != pS._stats.end(); i++, k++) {
            QString q = QString::number(i.value());
            ui->playerTable->setItem(j, k, new QTableWidgetItem(q));
            if (k == ui->playerTable->columnCount()-1) {
                k = 0;
                j++;
            }
        }
}

void Widget::jsonReader() {
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

    foreach(const QJsonValue & v, array) {

        if (v.toObject().value("Games").toDouble() == 0)
            continue;

        pS._name.insert(v.toObject().value("PlayerID").toInt(), v.toObject().value("Name").toString());
        pS._stats.insert(v.toObject().value("PlayerID").toInt(), v.toObject().value("FantasyPoints").toDouble());
        pS._stats.insert(v.toObject().value("PlayerID").toInt(), v.toObject().value("Points").toDouble() / v.toObject().value("Games").toDouble());
        pS._stats.insert(v.toObject().value("PlayerID").toInt(), v.toObject().value("BlockedShots").toDouble() / v.toObject().value("Games").toDouble());
        pS._stats.insert(v.toObject().value("PlayerID").toInt(), v.toObject().value("Steals").toDouble() / v.toObject().value("Games").toDouble());
        pS._stats.insert(v.toObject().value("PlayerID").toInt(), v.toObject().value("Assists").toDouble() / v.toObject().value("Games").toDouble());
        pS._stats.insert(v.toObject().value("PlayerID").toInt(), v.toObject().value("Rebounds").toDouble() / v.toObject().value("Games").toDouble());
        pS._stats.insert(v.toObject().value("PlayerID").toInt(), v.toObject().value("Games").toDouble());
    }
}




void Widget::on_buttonDownload_clicked()
{
    jsonReader();
    populateFirstColumn();
    populateRest();
}
