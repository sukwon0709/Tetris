#include "sblock.h"

using namespace std;

SBlock::SBlock(int lvl)
: Block(S, lvl)
{
    setCoords(0, firstX, firstY);
    setCoords(1, firstX + 1, firstY);
    setCoords(2, firstX + 1, firstY + 1);
    setCoords(3, firstX + 2, firstY + 1);
}

void SBlock::draw(ostream & out) const
{
    out << " SS" << endl;
    out << "SS";
}

char SBlock::getSymbol() const
{
    return 'S';
}

void SBlock::draw(Xwindow& w) const {
    w.fillRectangle(20, 40, 120, 80, Xwindow::Black);
    w.fillRectangle(50,80,19,19,Xwindow::Orange);
    w.fillRectangle(70,80,19,19,Xwindow::Orange);
    w.fillRectangle(70,60,19,19,Xwindow::Orange);
    w.fillRectangle(90,60,19,19,Xwindow::Orange);
}
