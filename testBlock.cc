#include <cassert>
#include <utility>
#include "block.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"

using namespace std;

/*
 * TEST SUITE for block methods
 *
 * This is a test suite we have written for block methods
 * To build this test type: make test_block
 * Run the executable ./testBlock to test
 * Nothing will get printed if all the tests in the suite passes
 * If a test fails, abort message will be printed
 *
 * The reason we have coded testing this way is because there's no c++ testing library
 * found in linux.student.cs.uwaterloo.ca machine (have looked for CppTest, googletest)
 * instead of including massive amount of library and building it ourselves
 * we thought this approach was sufficient for testing.
 */

// tests if block is initialized to correct coordinate
void initializeTest()
{
    Block * block = new IBlock(0);
    assert(block->getCoords(0).first == 0);
    assert(block->getCoords(0).second == 17);
    assert(block->getCoords(1).first == 1);
    assert(block->getCoords(1).second == 17);
    assert(block->getCoords(2).first == 2);
    assert(block->getCoords(2).second == 17);
    assert(block->getCoords(3).first == 3);
    assert(block->getCoords(3).second == 17);
    delete block;
    block = new JBlock(0);
    assert(block->getCoords(0).first == 0);
    assert(block->getCoords(0).second == 18);
    assert(block->getCoords(1).first == 0);
    assert(block->getCoords(1).second == 17);
    assert(block->getCoords(2).first == 1);
    assert(block->getCoords(2).second == 17);
    assert(block->getCoords(3).first == 2);
    assert(block->getCoords(3).second == 17);
    delete block;
    block = new LBlock(0);
    assert(block->getCoords(0).first == 0);
    assert(block->getCoords(0).second == 17);
    assert(block->getCoords(1).first == 1);
    assert(block->getCoords(1).second == 17);
    assert(block->getCoords(2).first == 2);
    assert(block->getCoords(2).second == 17);
    assert(block->getCoords(3).first == 2);
    assert(block->getCoords(3).second == 18);
    delete block;
    block = new OBlock(0);
    assert(block->getCoords(0).first == 0);
    assert(block->getCoords(0).second == 17);
    assert(block->getCoords(1).first == 1);
    assert(block->getCoords(1).second == 17);
    assert(block->getCoords(2).first == 0);
    assert(block->getCoords(2).second == 18);
    assert(block->getCoords(3).first == 1);
    assert(block->getCoords(3).second == 18);
    delete block;
    block = new SBlock(0);
    assert(block->getCoords(0).first == 0);
    assert(block->getCoords(0).second == 17);
    assert(block->getCoords(1).first == 1);
    assert(block->getCoords(1).second == 17);
    assert(block->getCoords(2).first == 1);
    assert(block->getCoords(2).second == 18);
    assert(block->getCoords(3).first == 2);
    assert(block->getCoords(3).second == 18);
    delete block;
    block = new ZBlock(0);
    assert(block->getCoords(0).first == 0);
    assert(block->getCoords(0).second == 18);
    assert(block->getCoords(1).first == 1);
    assert(block->getCoords(1).second == 18);
    assert(block->getCoords(2).first == 1);
    assert(block->getCoords(2).second == 17);
    assert(block->getCoords(3).first == 2);
    assert(block->getCoords(3).second == 17);
    delete block;
    block = new TBlock(0);
    assert(block->getCoords(0).first == 0);
    assert(block->getCoords(0).second == 18);
    assert(block->getCoords(1).first == 1);
    assert(block->getCoords(1).second == 18);
    assert(block->getCoords(2).first == 2);
    assert(block->getCoords(2).second == 18);
    assert(block->getCoords(3).first == 1);
    assert(block->getCoords(3).second == 17);
    delete block;

}

void moveTest(Block * block)
{
    pair<int, int> origCoords[4];
    for (int i=0; i<4; ++i) {
        origCoords[i] = block->getCoords(i);
    }
    block->move(Block::left);
    for (int i=0; i<4; ++i) {
        assert(block->getCoords(i).first == origCoords[i].first-1);
        assert(block->getCoords(i).second == origCoords[i].second);
    }

    // right
    block->move(Block::right);
    for (int i=0; i<4; ++i) {
        assert(block->getCoords(i).first == origCoords[i].first);
        assert(block->getCoords(i).second == origCoords[i].second);
    }

    // left
    block->move(Block::left);
    for (int i=0; i<4; ++i) {
        assert(block->getCoords(i).first == origCoords[i].first-1);
        assert(block->getCoords(i).second == origCoords[i].second);
    }

    // down
    block->move(Block::down);
    for (int i=0; i<4; ++i) {
        assert(block->getCoords(i).second == origCoords[i].second-1);
    }
    delete block;
}

int main()
{
    initializeTest();
    moveTest(new IBlock(0));
    moveTest(new JBlock(0));
    moveTest(new LBlock(0));
    moveTest(new OBlock(0));
    moveTest(new SBlock(0));
    moveTest(new TBlock(0));
    moveTest(new ZBlock(0));

    return 0;
}
