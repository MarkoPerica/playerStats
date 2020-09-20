#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H

#include <QMap>

class playerStats
{
public:
    playerStats();

    ~playerStats();

 //   void insertName(int key, QString value);
 //   void insertStats(int key, double value);


    QMap<int, QString> _name;
    QMultiMap<int, double> _stats;

};

#endif // PLAYERSTATS_H
