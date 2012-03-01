#ifndef __IBLOCK_H__
#define __IBLOCK_H__

#include "block.h"

/*
 * Class for an I-Block
 */

class IBlock : public Block {
public:
    IBlock(int level);

    void draw(std::ostream & out) const;
    void draw(Xwindow& w) const;
    char getSymbol() const;
};

#endif
