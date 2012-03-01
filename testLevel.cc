#include "iblock.h"
#include "level.h"
#include <cassert>

/*
 * TEST SUITE for general Level methods
 *
 * This is a test suite we have written for level methods
 * To build this test type: make test_level
 * Run the executable ./testLevel to test
 * Nothing will get printed if all the tests in the suite passes
 * If a test fails, abort message will be printed
 *
 * The reason we have coded testing this way is because there's no c++ testing library
 * found in linux.student.cs.uwaterloo.ca machine (have looked for CppTest, googletest)
 * instead of including massive amount of library and building it ourselves
 * we thought this approach was sufficient for testing.
 */

void lvlUpDownTest()
{
    Level lvl;

    assert(lvl.getLevel() == Level::LVL1);
    lvl.lvlUp();
    assert(lvl.getLevel() == Level::LVL2);
    lvl.lvlUp();
    assert(lvl.getLevel() == Level::LVL3);
    lvl.lvlUp();
    assert(lvl.getLevel() == Level::LVL3);
    lvl.lvlDown();
    assert(lvl.getLevel() == Level::LVL2);
    lvl.lvlDown();
    assert(lvl.getLevel() == Level::LVL1);
    lvl.lvlDown();
    assert(lvl.getLevel() == Level::LVL0);
    lvl.lvlDown();
    assert(lvl.getLevel() == Level::LVL0);
}

void scoreTest()
{
    Level lvl;

    // check initialization
    assert(lvl.getScore() == 0);
    assert(lvl.getHighScore() == 0);
    assert(lvl.getLevel() == Level::LVL1);

    // erases 3 rows
    lvl.updateScore();
    assert(lvl.getScore() == 4);
    assert(lvl.getHighScore() == 4);
    lvl.updateScore();
    assert(lvl.getScore() == 8);
    assert(lvl.getHighScore() == 8);
    lvl.updateScore();
    assert(lvl.getScore() == 12);
    assert(lvl.getHighScore() == 12);

    // levelup
    lvl.lvlUp();
    assert(lvl.getLevel() == Level::LVL2);
    // erases 3 rows
    lvl.updateScore();
    assert(lvl.getScore() == 21);
    assert(lvl.getHighScore() == 21);
    lvl.updateScore();
    assert(lvl.getScore() == 30);
    assert(lvl.getHighScore() == 30);
    lvl.updateScore();
    assert(lvl.getScore() == 39);
    assert(lvl.getHighScore() == 39);

    // levelup
    lvl.lvlUp();
    assert(lvl.getLevel() == Level::LVL3);
    // erases 3 rows
    lvl.updateScore();
    assert(lvl.getScore() == 55);
    assert(lvl.getHighScore() == 55);
    lvl.updateScore();
    assert(lvl.getScore() == 71);
    assert(lvl.getHighScore() == 71);
    lvl.updateScore();
    assert(lvl.getScore() == 87);
    assert(lvl.getHighScore() == 87);

    // level0
    lvl.lvlDown();
    lvl.lvlDown();
    lvl.lvlDown();
    assert(lvl.getLevel() == Level::LVL0);
    // erases 3 rows
    lvl.updateScore();
    assert(lvl.getScore() == 88);
    assert(lvl.getHighScore() == 88);
    lvl.updateScore();
    assert(lvl.getScore() == 89);
    assert(lvl.getHighScore() == 89);
    lvl.updateScore();
    assert(lvl.getScore() == 90);
    assert(lvl.getHighScore() == 90);
}

void eraseBlockScoreTest()
{
    Level lvl;

    IBlock * block = new IBlock(0);
    lvl.updateScore(*block);
    assert(lvl.getScore() == 1);
    assert(lvl.getHighScore() == 1);
    delete block;
    block = new IBlock(1);
    lvl.updateScore(*block);
    assert(lvl.getScore() == 5);
    assert(lvl.getHighScore() == 5);
    delete block;
    block = new IBlock(2);
    lvl.updateScore(*block);
    assert(lvl.getScore() == 14);
    assert(lvl.getHighScore() == 14);
    delete block;
    block = new IBlock(3);
    lvl.updateScore(*block);
    assert(lvl.getScore() == 30);
    assert(lvl.getHighScore() == 30);
}

void testReset()
{
    Level lvl;

    assert(lvl.getLevel() == Level::LVL1);
    lvl.lvlUp();
    lvl.lvlUp();
    lvl.getScore();
    lvl.reset();
    assert(lvl.getLevel() == Level::LVL1);
    assert(lvl.getScore() == 0);
    assert(lvl.getHighScore() == 0);
}

int main()
{
    lvlUpDownTest();
    scoreTest();
    eraseBlockScoreTest();

    return 0;
}
