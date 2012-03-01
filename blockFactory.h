#ifndef __BLOCKFACTORY_H_
#define __BLOCKFACTORY_H_

#include "block.h"

/*
 * Abstract base class for creating blocks. (Factory method)
 *
 * Subclasses will override getNextBlock() call to decide
 * which Block it will instantiate.
 * Possible blocks: I, J, L, O, S, T, Z
 */
class BlockFactory
{
public:
    // for correct destruction
    virtual ~BlockFactory() {}

    // Subclasses override this
    virtual Block* getNextBlock() = 0;
};

#endif // __BLOCKFACTORY_H_
