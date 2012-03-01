#ifndef __TBlock_H__
#define __TBlock_H__

#include "block.h"

class TBlock : public Block {
public:
    TBlock(int level);

    void draw(Xwindow& w) const;
    void draw(std::ostream & out) const;
    char getSymbol() const;
};

#endif
