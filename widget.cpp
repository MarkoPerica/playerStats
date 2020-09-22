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
    ui->playerTable->resizeRowsToContents();
    ui->playerTable->setMinimumHeight(500);

    downloader = new class downloader();

    connect(ui->buttonDownload, &QPushButton::clicked, downloader, &downloader::getData);
    connect(downloader, &downloader::onReady, this, &Widget::readFileAndPopulateTable);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::readFileAndPopulateTable() {
    auto i = 0;
    foreach(auto && value, downloader->jsonArray) {
        if (value.toObject().value("Games").toDouble() == 0)
            continue;
        ui->playerTable->setRowCount(i+1);
        for (auto j = 0; j < ui->playerTable->columnCount(); j++) {
            switch (j) {
            case 0: {
                auto *fCell = new QTableWidgetItem(value.toObject().value("Name").toString());
                ui->playerTable->setItem(i, j, fCell);
                break;
            }
            case 1: {
                QString games = QString::number(value.toObject().value("Games").toDouble());
                ui->playerTable->setItem(i, j, new QTableWidgetItem(games));
                break;
            }
            case 2: {
                QString rebounds = QString::number(value.toObject().value("Rebounds").toDouble() / value.toObject().value("Games").toDouble());
                ui->playerTable->setItem(i, j, new QTableWidgetItem(rebounds));
                break;
            }
            case 3: {
                QString assists = QString::number(value.toObject().value("Assists").toDouble() / value.toObject().value("Games").toDouble());
                ui->playerTable->setItem(i, j, new QTableWidgetItem(assists));
                break;
            }
            case 4: {
                QString steals = QString::number(value.toObject().value("Steals").toDouble() / value.toObject().value("Games").toDouble());
                ui->playerTable->setItem(i, j, new QTableWidgetItem(steals));
                break;
            }
            case 5: {
                QString blocks = QString::number(value.toObject().value("Blocks").toDouble() / value.toObject().value("Games").toDouble());
                ui->playerTable->setItem(i, j, new QTableWidgetItem(blocks));
                break;
            }
            case 6: {
                QString points = QString::number(value.toObject().value("Points").toDouble() / value.toObject().value("Games").toDouble());
                ui->playerTable->setItem(i, j, new QTableWidgetItem(points));
                break;
            }
            case 7: {
                QString fantasyPoints = QString::number(value.toObject().value("Fantasy Points").toDouble());
                ui->playerTable->setItem(i, j, new QTableWidgetItem(fantasyPoints));
                break;
            }
            }

        }
        i++;
    }

}


void Widget::on_buttonDownload_clicked()
{
}
