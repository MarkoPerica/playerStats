#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H

#include <QMap>

class playerStats
{
public:
    playerStats();

    ~playerStats();

    void insertName(int key, QString value);
    void insertGames(int key, int value);
    void insertRebounds(int key, double value);
    void insertAssists(int key, double value);
    void insertSteals(int key, double value);
    void insertBlocks(int key, double value);
    void insertPoints(int key, double value);
    void insertFantasyPoints(int key, double value);

    void reboundsPerGame();
    void assistsPerGame();
    void stealsPerGame();
    void blocksPerGame();
    void pointsPerGame();

    friend class widget;

    QMap<int, QString> _name;
    QMap<int, double> _games;
    QMap<int, double> _rebounds;
    QMap<int, double> _assists;
    QMap<int, double> _steals;
    QMap<int, double> _blocks;
    QMap<int, double> _points;
    QMap<int, double> _fantasyPoints;
};

#endif // PLAYERSTATS_H
