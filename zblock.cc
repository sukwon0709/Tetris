#include "zblock.h"

using namespace std;

ZBlock::ZBlock(int lvl)
: Block(Z, lvl)
{
    setCoords(0, firstX, firstY + 1);
    setCoords(1, firstX + 1, firstY + 1);
    setCoords(2, firstX + 1, firstY);
    setCoords(3, firstX + 2, firstY);
}

void ZBlock::draw(ostream & out) const
{
    out << "ZZ" << endl;
    out << " ZZ";
}

char ZBlock::getSymbol() const
{
    return 'Z';
}

void ZBlock::draw(Xwindow& w) const {
    w.fillRectangle(20, 40, 120, 80, Xwindow::Black);
    w.fillRectangle(50,60,19,19,Xwindow::Green);
    w.fillRectangle(70,60,19,19,Xwindow::Green);
    w.fillRectangle(70,80,19,19,Xwindow::Green);
    w.fillRectangle(90,80,19,19,Xwindow::Green);
}
