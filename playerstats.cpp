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

void playerStats::reboundsPerGame() {
    for(auto it_rebounds = _rebounds.begin(), end_rebounds = _rebounds.end(),
             it_games = _games.begin(), end_games = _games.end();
             it_rebounds != end_rebounds && it_games != end_games;) {

        it_rebounds.value() = it_rebounds.value() / it_games.value();
    }
}


void playerStats::assistsPerGame() {
    for(auto it_assists = _assists.begin(), end_assists = _assists.end(),
             it_games = _games.begin(), end_games = _games.end();
             it_assists != end_assists && it_games != end_games;) {

        it_assists.value() = it_assists.value() / it_games.value();
    }
}


void playerStats::blocksPerGame() {
    for(auto it_blocks = _blocks.begin(), end_blocks = _blocks.end(),
             it_games = _games.begin(), end_games = _games.end();
             it_blocks != end_blocks && it_games != end_games;) {

        it_blocks.value() = it_blocks.value() / it_games.value();
    }
}


void playerStats::stealsPerGame() {
    for(auto it_steals = _rebounds.begin(), end_steals = _rebounds.end(),
             it_games = _games.begin(), end_games = _games.end();
             it_steals != end_steals && it_games != end_games;) {

        it_steals.value() = it_steals.value() / it_games.value();
    }
}


void playerStats::pointsPerGame() {
    for(auto it_points = _rebounds.begin(), end_points = _rebounds.end(),
             it_games = _games.begin(), end_games = _games.end();
             it_points != end_points && it_games != end_games;) {

        it_points.value() = it_points.value() / it_games.value();
    }
}

