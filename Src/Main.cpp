#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream> // tmp
#include <list>
#include <SFML/Graphics.hpp>

#include "Board.hpp"
#include "AI.hpp"

using namespace std;
using namespace sf;

bool checkEnd(Board &board, AI &ai1, AI &ai2)
{
    Uint8 winner = board.getWinner();
    bool equality = board.getEquality();

    if (winner == emptyValue && equality == false)
        return false;

    if (winner != emptyValue)
    {
        ai1.learn(winner == 0 ? 1 : 0, winner == 0 ? 0 : 1);
        ai2.learn(winner == 1 ? 1 : 0, winner == 1 ? 0 : 1);
    }

    ai1.clear();
    ai2.clear();
    board.clear();
    
    return true;
}

void step(Board &board, AI &ai1, AI &ai2, Uint8 &nextPlayer, Uint8 forcePlay = emptyValue)
{
    if (checkEnd(board, ai1, ai2) == true)
        return;

    vector<Uint8> boardStats(boardSize.x * boardSize.y);
    for (Uint8 i = 0; i < boardSize.x; i++)
        for (Uint8 j = 0; j < boardSize.y; j++)
            boardStats[i * boardSize.x + j] = board.getCell(Vector2b(i, j));

    Uint8 index;

    if (nextPlayer == 0)
    {
        index = ai1.play(boardStats, forcePlay);
    }
    else if (nextPlayer == 1)
    {
        index = ai2.play(boardStats, forcePlay);
    }
    
    board.setValue(Vector2b(index / boardSize.x, index % boardSize.y), nextPlayer);
    nextPlayer = (nextPlayer + 1) % 2;
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    RenderWindow window(VideoMode(boardSize.x * 200, boardSize.y * 200), "TicTacToe-MachineLearning");

    bool learingMode = false;
    Board board;
    AI ai1;
    AI ai2;
    Uint8 nextPlayer = rand() % 2;

    window.setFramerateLimit(30);
    while (window.isOpen())
    {
        for (Event event; window.pollEvent(event);)
        {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseButtonPressed)
            {
                Vector2b mouseGridPosition;
                mouseGridPosition.x = event.mouseButton.x / (window.getSize().x / boardSize.x);
                mouseGridPosition.y = event.mouseButton.y / (window.getSize().y / boardSize.y);

                step(board, ai1, ai2, nextPlayer, mouseGridPosition.x * boardSize.x + mouseGridPosition.y);
            }
            else if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::W)
                {
                    step(board, ai1, ai2, nextPlayer);
                }
                else if (event.key.code == Keyboard::L)
                {
                    learingMode = !learingMode;

                    if (learingMode == false)
                    {
                        window.setFramerateLimit(30);
                    }
                    else
                    {
                        window.setFramerateLimit(0);
                        window.clear(Color(20, 20, 150));
                        window.display();
                    }
                }
            }
        }

        if (learingMode == false)
        {
            window.clear(Color(20, 20, 20));
            window.draw(board);
            window.display();
        }
        else
        {
            step(board, ai1, ai2, nextPlayer);
        }
    }
    return 0;
}