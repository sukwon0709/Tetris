#ifndef __ZBlock_H__
#define __ZBlock_H__

#include "block.h"

class ZBlock : public Block {
public:
    ZBlock(int lvl);

    void draw(Xwindow& w) const;
    void draw(std::ostream & out) const;
    char getSymbol() const;
};

#endif
