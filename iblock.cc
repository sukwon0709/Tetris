#include "iblock.h"

using namespace std;

IBlock::IBlock(int lvl)
: Block(I, lvl)
{
    for (int i = 0; i < 4; i++) {
        setCoords(i, firstX + i, firstY);
    }
}

void IBlock::draw(ostream & out) const
{
    out << "IIII";
}

char IBlock::getSymbol() const
{
    return 'I';
}

void IBlock::draw(Xwindow& w) const {
	w.fillRectangle(20, 40, 120, 80, Xwindow::Black);
	w.fillRectangle(40,70,19,19,Xwindow::Red);
	w.fillRectangle(60,70,19,19,Xwindow::Red);
	w.fillRectangle(80,70,19,19,Xwindow::Red);
	w.fillRectangle(100,70,19,19,Xwindow::Red);
}
