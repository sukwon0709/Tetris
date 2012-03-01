#ifndef __SBlock_H__
#define __SBlock_H__

#include "block.h"

class SBlock : public Block {
public:
    SBlock(int level);

    void draw(Xwindow& w) const;
    void draw(std::ostream & out) const;
    char getSymbol() const;
};

#endif
