#ifndef __BLOCKFACTORY_LEVEL3_H_
#define __BLOCKFACTORY_LEVEL3_H_

#include "blockFactory.h"

/*
 * Concrete factory for creating block when Level is 3
 *
 * Creates blocks randomly with probabilities skewed such that
 * S/Z blocks are created in probability of 2/9
 * and other blocks are created in probability of 1/9 each.
 */
class BlockFactoryLevel3 : public BlockFactory
{
public:
    Block* getNextBlock();
};

#endif // __BLOCKFACTORY_LEVEL3_H_
