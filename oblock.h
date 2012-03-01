#ifndef __OBlock_H__
#define __OBlock_H__

#include "block.h"

class OBlock : public Block {
public:
    OBlock(int level);

    void draw(Xwindow& w) const;
    void draw(std::ostream & out) const;
    char getSymbol() const;
};

#endif
