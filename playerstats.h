#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H

#include <QMap>

class playerStats
{
public:
    playerStats();
private:
    QMap<int, QString> name;
    QMap<int, int> games;
    QMap<int, double> rebounds;
    QMap<int, double> assists;
    QMap<int, double> steals;
    QMap<int, double> blocks;
    QMap<int, double> points;
    QMap<int, double> fantasyPoints;

};

#endif // PLAYERSTATS_H
