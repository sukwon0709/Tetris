#ifndef __BLOCKFACTORY_LEVEL2_H_
#define __BLOCKFACTORY_LEVEL2_H_

#include "blockFactory.h"

/*
 * Concrete factory for creating block when Level is 2
 *
 * Creates blocks randomly with equal probabilities
 * all blocks are instantiated with probability of 1/7 each.
 */
class BlockFactoryLevel2 : public BlockFactory
{
public:
    Block* getNextBlock();
};

#endif // __BLOCKFACTORY_LEVEL2_H_
