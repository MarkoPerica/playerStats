#include "playerstats.h"

playerStats::playerStats()
{

}

playerStats::~playerStats() {

}

void playerStats::insertName(int key, QString value) {
    _name.insert(key, value);
}

void playerStats::insertGames(int key, int value) {
    _games.insert(key, value);
}
void playerStats::insertRebounds(int key, double value) {
    _rebounds.insert(key, value);
}
void playerStats::insertAssists(int key, double value) {
    _assists.insert(key, value);
}
void playerStats::insertSteals(int key, double value) {
    _steals.insert(key, value);
}
void playerStats::insertBlocks(int key, double value) {
    _blocks.insert(key, value);
}
void playerStats::insertPoints(int key, double value) {
    _points.insert(key, value);
}
void playerStats::insertFantasyPoints(int key, double value) {
    _fantasyPoints.insert(key, value);
}

