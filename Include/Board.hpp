#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

using namespace std;
using namespace sf;

typedef Vector2<Uint8> Vector2b; // 'b' for byte

#define boardSize Vector2b(3, 3)
#define emptyValue ((Uint8)-1)

class Board : public Drawable, public Transformable
{
public:
    Board();
    ~Board();
    const Vector2b &getSize() const;
    const Uint8 &getCell(const Vector2b &position) const;
    void clear();
    void setValue(const Vector2b &position, Uint8 value);
    Uint8 getWinner() const;
    bool getEquality() const;
    void draw(RenderTarget &target, RenderStates states) const;

private:
    Uint8 checkLine(const Vector2b &position, const Vector2<Int8> &direction, Uint8 alignmentRequired) const;

private:
    Vector2b size;
    Uint8 **tab;
};
