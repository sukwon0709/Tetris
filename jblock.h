#ifndef __JBlock_H__
#define __JBlock_H__

#include "block.h"

/*
 * Class for a J-Block
 */

class JBlock : public Block {
public:
    JBlock(int level);

    void draw(Xwindow& w) const;
    void draw(std::ostream & out) const;
    char getSymbol() const;
};

#endif
