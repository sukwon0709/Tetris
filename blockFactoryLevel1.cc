#include "blockFactoryLevel1.h"
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
Block* BlockFactoryLevel1::getNextBlock()
{
    Block* nextBlock = NULL;

    // Gets the singleton instance of random number generator (wraps PRNG)
    RndNumGenerator& rndGen = RndNumGenerator::getInstance();
    uint32_t num = rndGen(0, 11); // randomly generated number from 0 ~ 11

    // 1 out of 12 numbers - SBlock
    // 1 out of 12 numbers - ZBlock
    // 2 out of 12 numbers - each of rest of blocks
    switch (num) {
        case 0:
            nextBlock = new SBlock(Level::LVL1);
            break;
        case 1:
            nextBlock = new ZBlock(Level::LVL1);
            break;
        case 2:
        case 3:
            nextBlock = new IBlock(Level::LVL1);
            break;
        case 4:
        case 5:
            nextBlock = new JBlock(Level::LVL1);
            break;
        case 6:
        case 7:
            nextBlock = new LBlock(Level::LVL1);
            break;
        case 8:
        case 9:
            nextBlock = new OBlock(Level::LVL1);
            break;
        case 10:
        case 11:
            nextBlock = new TBlock(Level::LVL1);
            break;
        default:
            assert(0); // shouldn't happen
            break;
    }

    // will not be null
    return nextBlock;
}
