#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream> // tmp
#include <list>
#include <SFML/Graphics.hpp>

#include "Board.hpp"
#include "AI.hpp"

using namespace std;
using namespace sf;

void step(Board &board, AI &ai1, AI &ai2, Uint8 &nextPlayer)
{
    Uint8 winner = board.getWinner();
    if (winner != emptyValue)
    {
        ai1.learn(winner == 0 ? 1 : 0, winner == 0 ? 0 : 1);
        ai2.learn(winner == 1 ? 1 : 0, winner == 1 ? 0 : 1);
    }

    if (winner != emptyValue || board.getEquality() == true)
    {
        ai1.clear();
        ai2.clear();
        board.clear();
        return;
    }

    vector<Uint8> boardStats(boardSize.x * boardSize.y);
    for (Uint8 i = 0; i < boardSize.x; i++)
        for (Uint8 j = 0; j < boardSize.y; j++)
            boardStats[i * boardSize.x + j] = board.getCell(Vector2b(i, j));

    Uint8 index;

    if (nextPlayer == 0)
    {
        index = ai1.play(boardStats);
    }
    else if (nextPlayer == 1)
    {
        index = ai2.play(boardStats);
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
                step(board, ai1, ai2, nextPlayer);
            }
            else if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::L)
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