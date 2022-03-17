#include <SFML/System/Vector2.hpp>
#include <iostream> // tmp
#include <list>

#include <SFML/Graphics.hpp>
#include "Board.hpp"

using namespace std;
using namespace sf;

int main(int argc, char **argv)
{
    RenderWindow window(VideoMode(boardSize.x * 200, boardSize.y * 200), "TicTacToe-MachineLearning");

    Board board;

    srand(time(NULL));

    window.setFramerateLimit(30);
    while (window.isOpen())
    {
        for (Event event; window.pollEvent(event);)
        {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseButtonPressed)
            {
                if (board.getWinner() == emptyValue)
                    board.setValue(Vector2b(rand() % boardSize.x, rand() % boardSize.y), rand() % 2);
                else
                    board.clear();
            }
        }

        window.clear(Color(20, 20, 20));
        window.draw(board);
        window.display();
    }
    return 0;
}