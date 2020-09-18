#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QStringList header;
    header << "Name" << "Games" << "Rebounds" << "Assits" << "Steals" << "Blocks" << "Points" << "Fantasy Points";
    setWindowTitle("Player Stats");
    ui->playerTable->setColumnCount(8);
    ui->playerTable->setHorizontalHeaderLabels(header);
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

    foreach(const QJsonValue & v, array) {
        pS->insertName(v.toObject().value("PlayerID").toInt(),v.toObject().value("Name").toString());
        pS->insertGames(v.toObject().value("PlayerID").toInt(),v.toObject().value("Games").toDouble());
        pS->insertRebounds(v.toObject().value("PlayerID").toInt(),v.toObject().value("Rebounds").toDouble());
        pS->insertAssists(v.toObject().value("PlayerID").toInt(),v.toObject().value("Assists").toDouble());
        pS->insertSteals(v.toObject().value("PlayerID").toInt(),v.toObject().value("Steals").toDouble());
        pS->insertBlocks(v.toObject().value("PlayerID").toInt(),v.toObject().value("Blocks").toDouble());
        pS->insertPoints(v.toObject().value("PlayerID").toInt(),v.toObject().value("Points").toDouble());
        pS->insertFantasyPoints(v.toObject().value("PlayerID").toInt(),v.toObject().value("FantasyPoints").toDouble());
    }
}
