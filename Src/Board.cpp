#include "Board.hpp"

Board::Board()
{
    size = boardSize;

    tab = new Uint8* [size.x];
    for (Uint8 i = 0; i < size.x; i++)
        tab[i] = new Uint8 [size.y];

    clear();
}

Board::~Board()
{
    for (Uint8 i = 0; i < size.x; i++)
        delete [] tab[i];
    delete [] tab;
}

void Board::clear()
{
    for (Uint8 i = 0; i < size.x; i++)
        for (Uint8 j = 0; j < size.y; j++)
            tab[i][j] = emptyValue;
}

void Board::setValue(const Vector2b &position, Uint8 value)
{
    if (tab[position.x][position.y] != emptyValue)
        return;

    tab[position.x][position.y] = value;
}

Uint8 Board::getWinner() const
{
    const Uint8 alignmentRequired = 3;

    for (Uint8 i = 0; i < size.x - alignmentRequired + 1; i++)
        for (Uint8 j = 0; j < size.y; j++)
        {
            Uint8 winner = checkLine(Vector2b(i, j), Vector2<Int8>(1, 0), alignmentRequired);
            if (winner != emptyValue)
                return winner;
        }

    for (Uint8 i = 0; i < size.x; i++)
        for (Uint8 j = 0; j < size.y - alignmentRequired + 1; j++)
        {
            Uint8 winner = checkLine(Vector2b(i, j), Vector2<Int8>(0, 1), alignmentRequired);
            if (winner != emptyValue)
                return winner;
        }

    for (Uint8 i = 0; i < size.x - alignmentRequired + 1; i++)
        for (Uint8 j = 0; j < size.y - alignmentRequired + 1; j++)
        {
            Uint8 winner = checkLine(Vector2b(i, j), Vector2<Int8>(1, 1), alignmentRequired);
            if (winner != emptyValue)
                return winner;
        }

    for (Uint8 i = alignmentRequired - 1; i < size.x; i++)
        for (Uint8 j = 0; j < size.y - alignmentRequired + 1; j++)
        {
            Uint8 winner = checkLine(Vector2b(i, j), Vector2<Int8>(-1, 1), alignmentRequired);
            if (winner != emptyValue)
                return winner;
        }

    return emptyValue;
}

void Board::draw(RenderTarget &target, RenderStates states) const
{
    Texture cellTexture;
    cellTexture.loadFromFile("Resources/Textures/Cell.png");
    Sprite cellSprite(cellTexture);

    Texture textures[2];
    textures[0].loadFromFile("Resources/Textures/Cross.png");
    textures[1].loadFromFile("Resources/Textures/Circle.png");

    Sprite sprite;

    for (Uint8 i = 0; i < size.x; i++)
        for (Uint8 j = 0; j < size.y; j++)
        {
            cellSprite.setPosition(i * 200, j * 200);
            target.draw(cellSprite, states);

            if (tab[i][j] != emptyValue)
            {
                sprite.setTexture(textures[tab[i][j]]);
                sprite.setPosition(i * 200, j * 200);
                target.draw(sprite, states);
            }
        }
}

Uint8 Board::checkLine(const Vector2b &position, const Vector2<Int8> &direction, Uint8 alignmentRequired) const
{
    Uint8 winner = tab[position.x][position.y];

    for (Uint8 i = 1; i < alignmentRequired; i++)
        if (tab[position.x + i * direction.x][position.y + i * direction.y] != winner)
            return emptyValue;
    
    return winner;
}