#include "blockFactoryLevel3.h"
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
Block* BlockFactoryLevel3::getNextBlock()
{
    Block* nextBlock = NULL;

    // Gets the singleton instance of random number generator (wraps PRNG)
    RndNumGenerator& rndGen = RndNumGenerator::getInstance();
    uint32_t num = rndGen(0, 8); // randomly generated number from 0 ~ 8

    // 2 out of 9 numbers - SBlock
    // 2 out of 9 numbers - ZBlock
    // 1 out of 9 numbers - each of rest of blocks
    switch (num) {
        case 0:
        case 1:
            nextBlock = new SBlock(Level::LVL3);
            break;
        case 2:
        case 3:
            nextBlock = new ZBlock(Level::LVL3);
            break;
        case 4:
            nextBlock = new IBlock(Level::LVL3);
            break;
        case 5:
            nextBlock = new JBlock(Level::LVL3);
            break;
        case 6:
            nextBlock = new LBlock(Level::LVL3);
            break;
        case 7:
            nextBlock = new OBlock(Level::LVL3);
            break;
        case 8:
            nextBlock = new TBlock(Level::LVL3);
            break;
        default:
            assert(0); // shouldn't happen
            break;
    }

    // will not be null
    return nextBlock;
}
