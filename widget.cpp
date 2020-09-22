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
    ui->playerTable->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    ui->playerTable->resizeRowsToContents();

    m_outlinePen.setColor(Qt::green);
    m_transparentBrush.setColor(Qt::transparent);

    downloader = new class downloader();

    schedule = new class schedule();

    connect(ui->buttonDownload, &QPushButton::clicked, downloader, &downloader::getData);
    connect(downloader, &downloader::onReady, this, &Widget::readFile);
    connect(ui->buttonDownload, &QPushButton::clicked, schedule, &schedule::getData);
    connect(ui->playerTable, &QTableWidget::cellClicked, this, &Widget::cellClicked);
}

Widget::~Widget()
{
    delete downloader;
    delete schedule;
    delete ui->playerTable;
    delete ui->buttonDownload;
    delete ui;
}

QString Widget::to_str(const QJsonValue &value, const std::string &name) {
    return value.toObject().value(name.c_str()).toString();
}

double Widget::to_num(const QJsonValue &value, const std::string &name) {
    return value.toObject().value(name.c_str()).toDouble();
}

QString Widget::per_game(const QJsonValue &value, const std::string &name, double games) {
    return QString::number(to_num(value, name) / games);
}

QDate Widget::transformDate(const QString date) {
    int pos = date.lastIndexOf(QChar('T'));
    QString s = date.left(pos);
    QString year = s.mid(0,4);
    QString month = s.mid(4, 4);
    QString day = s.mid(8, 2);
    QString ret;
    ret.append(day).append(month).append(year);
    ret.replace("-", ".");
    return QDate::fromString(ret);
}


void Widget::readFile() {
    auto row = 0;
    foreach(const auto& value, downloader->jsonArray) {
        auto games = to_num(value, "Games");
        if (games == 0) continue;
        ui->playerTable->setRowCount(row+1);
        auto col = 0;
        ui->playerTable->setItem(row, col++, new QTableWidgetItem(to_str(value, "Name")));
        ui->playerTable->setItem(row, col++, new QTableWidgetItem(QString::number(games)));
        ui->playerTable->setItem(row, col++, new QTableWidgetItem(per_game(value, "Rebounds", games)));
        ui->playerTable->setItem(row, col++, new QTableWidgetItem(per_game(value, "Assists", games)));
        ui->playerTable->setItem(row, col++, new QTableWidgetItem(per_game(value, "Steals", games)));
        ui->playerTable->setItem(row, col++, new QTableWidgetItem(per_game(value, "BlockedShots", games)));
        ui->playerTable->setItem(row, col++, new QTableWidgetItem(per_game(value, "Points", games)));
        ui->playerTable->setItem(row, col++, new QTableWidgetItem(QString::number(to_num(value, "FantasyPoints"))));
        ++row;
    }
}

void Widget::on_buttonDownload_clicked()
{

}


void Widget::cellClicked(int iRow)
{
    QTableWidgetItem *item = new QTableWidgetItem;
    item = ui->playerTable->item(iRow, 0);
    auto teamID = downloader->players.value(item->text());

    QMultiMap<int, int>::const_iterator i;
    for (i = schedule->games.begin(); i != schedule->games.end(); i++) {
        if (teamID == i.value())
            keys.append(i.key());
    }

    QList<int>::const_iterator j;
    for (j = keys.constBegin(); j != keys.constEnd(); ++j) {
        auto date = schedule->date.value(*j);
        QTextCharFormat format;
        format.setUnderlineColor(Qt::green);
        ui->calendarWidget->setDateTextFormat(transformDate(date), format);
    }

}
