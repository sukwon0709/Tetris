#ifndef __BLOCKFACTORY_LEVEL0_H_
#define __BLOCKFACTORY_LEVEL0_H_

#include "blockFactory.h"
#include <fstream>

/*
 * Concrete factory for creating block when Level is 0
 *
 * Creates blocks in sequence from the file ("sequence.txt").
 * The game will restart when the file is read completely.
 */
class BlockFactoryLevel0 : public BlockFactory
{
public:
    BlockFactoryLevel0(std::ifstream & file);

    // throws FileIOException
    Block* getNextBlock();

private:
    std::ifstream & file;
};

#endif // __BLOCKFACTORY_LEVEL0_H_
