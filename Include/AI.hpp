#include <vector>
#include <map>
#include <SFML/Config.hpp>
#include "Board.hpp"

#pragma once

using namespace std;
using namespace sf;

class AI
{
public:
    //AI();
    // TODO save and load
    void clear();
    Uint8 play(const vector<Uint8> &boardStats, Uint8 forcePlay = emptyValue);
    void learn(Uint8 reward, Uint8 punish);

private:
    Uint8 randomPlay(const vector<Uint8> &boardStats) const;
    bool checkMemoryCellEmpty(const vector<Uint8> &memoryCell) const;

private:
    static map<vector<Uint8>, vector<Uint8>> memory;
    vector<pair<vector<Uint8>, Uint8>> playHistory;
};