#ifndef __LBlock_H__
#define __LBlock_H__

#include "block.h"

class LBlock : public Block {
public:
    LBlock(int level);
    
    void draw(Xwindow& w) const;
    void draw(std::ostream & out) const;
    char getSymbol() const;
};

#endif
