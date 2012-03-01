#include "tblock.h"

using namespace std;

TBlock::TBlock(int lvl)
: Block(T, lvl)
{
    for (int i = 0; i < 3; i++) {
        setCoords(i, firstX + i, firstY + 1);
    }
    setCoords(3, firstX + 1, firstY);
}

void TBlock::draw(ostream & out) const
{
    out << "TTT" << endl;
    out << " T";
}

char TBlock::getSymbol() const
{
    return 'T';
}

void TBlock::draw(Xwindow& w) const {
    w.fillRectangle(20, 40, 120, 80, Xwindow::Black);
    w.fillRectangle(50,60,19,19,Xwindow::Brown);
    w.fillRectangle(70,60,19,19,Xwindow::Brown);
    w.fillRectangle(90,60,19,19,Xwindow::Brown);
    w.fillRectangle(70,80,19,19,Xwindow::Brown);
}
