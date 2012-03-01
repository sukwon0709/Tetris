#include "oblock.h"

using namespace std;

OBlock::OBlock(int lvl)
: Block(O, lvl)
{
    setCoords(0, firstX, firstY);
    setCoords(1, firstX + 1, firstY);
    setCoords(2, firstX, firstY + 1);
    setCoords(3, firstX + 1, firstY + 1);
}

void OBlock::draw(ostream & out) const
{
    out << "OO" << endl;
    out << "OO";
}

char OBlock::getSymbol() const
{
    return 'O';
}

void OBlock::draw(Xwindow& w) const {
    w.fillRectangle(20, 40, 120, 80, Xwindow::Black);
    w.fillRectangle(60,60,19,19,Xwindow::Blue);
    w.fillRectangle(60,80,19,19,Xwindow::Blue);
    w.fillRectangle(80,60,19,19,Xwindow::Blue);
    w.fillRectangle(80,80,19,19,Xwindow::Blue);
}
