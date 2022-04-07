#include <stdlib.h>
#include "AI.hpp"
#include "Board.hpp"

#include <iostream> // tmp

map<vector<Uint8>, vector<Uint8>> AI::memory;

void AI::clear()
{
    playHistory.clear();
}

Uint8 AI::play(const vector<Uint8> &boardStats)
{
    auto search = memory.find(boardStats);
    vector<Uint8> memoryCell;
    Uint8 playIndex;

    if (search == memory.end())
    {
        memoryCell.resize(boardStats.size());
        for (Uint8 i = 0; i < boardStats.size(); i++)
                memoryCell[i] = boardStats[i] == emptyValue;

        memory[boardStats] = memoryCell;
    }
    else
    {
        memoryCell = search->second;
    }

    vector<Uint8> playChoices;
    for (Uint8 i = 0; i < memoryCell.size(); i++)
        playChoices.insert(playChoices.end(), memoryCell[i], i);

    playIndex = playChoices[rand() % playChoices.size()];

    playHistory.push_back(make_pair<vector<Uint8>, Uint8>(vector<Uint8>(boardStats), Uint8(playIndex)));

    return playIndex;
}

void AI::learn(Uint8 reward, Uint8 punish)
{
    /*
    cout << "Play history : " << endl;
    cout << "reward(" << (int)reward << ") punish(" << (int)punish << ")" << endl;

    for (Uint8 h = 0; h < playHistory.size(); h++)
    {
        for (Uint8 i = 0; i < boardSize.x; i++)
        {
            for (Uint8 j = 0; j < boardSize.y; j++)
            {
                if (i * boardSize.x + j == playHistory[h].second)
                    cout << "X";
                else if (playHistory[h].first[i * boardSize.x + j] == emptyValue)
                    cout << ".";
                else
                    cout << (char)(playHistory[h].first[i * boardSize.x + j] + '0');
            }
            cout << endl;
        }
        cout << endl;
    }
    */

    vector<Uint8> &memoryCell = memory[playHistory.back().first];
    Uint8 &playValue = memoryCell[playHistory.back().second];
    playValue = playValue > punish ? playValue - punish : 0;
    
    if (checkMemoryCellEmpty(memoryCell))
    {
        memory.erase(playHistory.back().first);

        playHistory.pop_back();

        learn(reward, punish);
    }
}

bool AI::checkMemoryCellEmpty(const vector<Uint8> &memoryCell) const
{
    for (Uint8 i = 0; i < memoryCell.size(); i++)
        if (memoryCell[i] != 0)
            return false;

    return true;
}