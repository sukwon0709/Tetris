#include "jblock.h"

using namespace std;

JBlock::JBlock(int lvl)
: Block(J, lvl)
{
    setCoords(0, firstX, firstY + 1);
    for (int i = 0; i < 3; i++) {
        setCoords(i+1, firstX + i, firstY);
    }
}

void JBlock::draw(ostream & out) const
{
    out << "J" << endl;
    out << "JJJ";
}

char JBlock::getSymbol() const
{
    return 'J';
}

void JBlock::draw(Xwindow& w) const {
    w.fillRectangle(20, 40, 120, 80, Xwindow::Black);
    w.fillRectangle(50,60,19,19,Xwindow::Magenta);
    w.fillRectangle(50,80,19,19,Xwindow::Magenta);
    w.fillRectangle(70,80,19,19,Xwindow::Magenta);
    w.fillRectangle(90,80,19,19,Xwindow::Magenta);
}
