#include "lblock.h"

using namespace std;

LBlock::LBlock(int lvl)
: Block(L, lvl)
{
    setCoords(3, firstX + 2, firstY + 1);
    for (int i = 0; i < 3; i++) {
        setCoords(i, firstX + i, firstY);
    }
}

void LBlock::draw(ostream & out) const
{
    out << "  L" << endl;
    out << "LLL";
}

char LBlock::getSymbol() const
{
    return 'L';
}

void LBlock::draw(Xwindow& w) const {
    w.fillRectangle(20, 40, 120, 80, Xwindow::Black);
    w.fillRectangle(90,60,19,19,Xwindow::Cyan);
    w.fillRectangle(90,80,19,19,Xwindow::Cyan);
    w.fillRectangle(70,80,19,19,Xwindow::Cyan);
    w.fillRectangle(50,80,19,19,Xwindow::Cyan);
}
