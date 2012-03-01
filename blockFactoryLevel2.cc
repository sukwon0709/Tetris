#include "blockFactoryLevel2.h"
#include <cassert>

#include "level.h"
#include "RndNumGenerator.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"

/*
 * Returns newly instantiated block instance
 * according to the random number generated from RndNumGenerator class
 *
 * @returns pointer to newly created block instance
 */
Block* BlockFactoryLevel2::getNextBlock()
{
    Block* nextBlock = NULL;

    // Gets the singleton instance of random number generator (wraps PRNG)
    RndNumGenerator& rndGen = RndNumGenerator::getInstance();
    uint32_t num = rndGen(0, 6); // randomly generated number from 0 ~ 7

    // 1 out of 7 numbers - each block
    switch (num) {
        case 0:
            nextBlock = new SBlock(Level::LVL2);
            break;
        case 1:
            nextBlock = new ZBlock(Level::LVL2);
            break;
        case 2:
            nextBlock = new IBlock(Level::LVL2);
            break;
        case 3:
            nextBlock = new JBlock(Level::LVL2);
            break;
        case 4:
            nextBlock = new LBlock(Level::LVL2);
            break;
        case 5:
            nextBlock = new OBlock(Level::LVL2);
            break;
        case 6:
            nextBlock = new TBlock(Level::LVL2);
            break;
        default:
            assert(0); // shouldn't happen
            break;
    }

    // will not be null
    return nextBlock;
}
