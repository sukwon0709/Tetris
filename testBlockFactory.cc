#include "level.h"
#include <cassert>
#include <iostream>
#include "block.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"

/*
 * TEST SUITE for generating next block
 *
 * This is a test suite we have written for generating next block
 * To build this test type: make test_blockFactory
 * Run the executable ./testBlockFactory to test
 * Nothing will get printed if all the tests in the suite passes
 * If a test fails, abort message will be printed
 *
 * The reason we have coded testing this way is because there's no c++ testing library
 * found in linux.student.cs.uwaterloo.ca machine (have looked for CppTest, googletest)
 * instead of including massive amount of library and building it ourselves
 * we thought this approach was sufficient for testing.
 */

// somehow couldn't use cmath's abs
double abs(double a)
{
    if (a < 0.0) {
        return -1*a;
    }
    return a;
}

// generates 1000000 blocks and make sure the required probability constraint is satisfied
void testGetNextBlock(Level & lvl)
{
    int sblock = 0;
    int zblock = 0;
    int iblock = 0;
    int jblock = 0;
    int lblock = 0;
    int oblock = 0;
    int tblock = 0;

    int numBlocks = 1000000;
    for (int i=0; i<numBlocks; ++i) {
        Block * block = lvl.getNextBlock();
        if (dynamic_cast<SBlock*>(block)) {
            sblock++;
        } else if (dynamic_cast<ZBlock*>(block)) {
            zblock++;
        } else if (dynamic_cast<IBlock*>(block)) {
            iblock++;
        } else if (dynamic_cast<JBlock*>(block)) {
            jblock++;
        } else if (dynamic_cast<LBlock*>(block)) {
            lblock++;
        } else if (dynamic_cast<OBlock*>(block)) {
            oblock++;
        } else if (dynamic_cast<TBlock*>(block)) {
            tblock++;
        } else {
            assert(0);
        }
        delete block;
    }

    // Level 1 requirements
    // S, Z blocks - 1/12 each
    // other blocks - 1/6 each
    double sprob = 0;
    double zprob = 0;
    double othersprob = 0;
    switch (lvl.getLevel()) {
        case Level::LVL1:
            sprob = zprob = 1.0/12;
            othersprob = 1.0/6;
            break;
        case Level::LVL2:
            sprob = zprob = othersprob = 1.0/7;
            break;
        case Level::LVL3:
            sprob = zprob = 2.0/9;
            othersprob = 1.0/9;
            break;
        default:
            assert(0);
    }
    assert(abs((double)sblock/numBlocks - sprob) < 0.001);
    assert(abs((double)zblock/numBlocks - zprob) < 0.001);
    assert(abs((double)iblock/numBlocks - othersprob) < 0.001);
    assert(abs((double)jblock/numBlocks - othersprob) < 0.001);
    assert(abs((double)lblock/numBlocks - othersprob) < 0.001);
    assert(abs((double)oblock/numBlocks - othersprob) < 0.001);
    assert(abs((double)tblock/numBlocks - othersprob) < 0.001);
}

int main()
{
    Level lvl;

    // level1
    testGetNextBlock(lvl);

    // level2
    lvl.lvlUp();
    testGetNextBlock(lvl);

    // level3
    lvl.lvlUp();
    testGetNextBlock(lvl);

    return 0;
}
