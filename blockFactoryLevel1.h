#ifndef __BLOCKFACTORY_LEVEL1_H_
#define __BLOCKFACTORY_LEVEL1_H_

#include "blockFactory.h"

/*
 * Concrete factory for creating block when Level is 1
 *
 * Creates blocks randomly with probabilities skewed such that
 * S/Z blocks are created in probability of 1/12
 * and other blocks are created in probability of 1/6 each.
 */
class BlockFactoryLevel1 : public BlockFactory
{
public:
    Block* getNextBlock();
};

#endif // __BLOCKFACTORY_LEVEL1_H_
