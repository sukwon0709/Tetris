#include "blockFactoryLevel0.h"
#include <cassert>
#include <iostream>
#include <string>

#include "level.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"

#include "exceptions.h"

using namespace std;

/*
 * Constructor
 *
 * @param file ifstream to file "sequence.txt"
 */
BlockFactoryLevel0::BlockFactoryLevel0(ifstream & file)
: file(file)
{}

/*
 * Returns newly instantiated block instance
 * according to the entries in sequence.txt
 *
 * @throws FileIOException error on reading sequence.txt
 * @returns pointer to newly created block instance
 */
Block* BlockFactoryLevel0::getNextBlock()
{
    Block * nextBlock = NULL;

    // reads a next block in sequence.txt
    string blockName;
    file >> blockName;

    /*
     * Throws an exception when an error occured in reading sequence.txt
     */
    if (!file) {
        throw FileIOException("Error on reading sequence.txt");
    }

    if (blockName == "I") {
        nextBlock = new IBlock(Level::LVL0);
    } else if (blockName == "J") {
        nextBlock = new JBlock(Level::LVL0);
    } else if (blockName == "L") {
        nextBlock = new LBlock(Level::LVL0);
    } else if (blockName == "O") {
        nextBlock = new OBlock(Level::LVL0);
    } else if (blockName == "S") {
        nextBlock = new SBlock(Level::LVL0);
    } else if (blockName == "T") {
        nextBlock = new TBlock(Level::LVL0);
    } else if (blockName == "Z") {
        nextBlock = new ZBlock(Level::LVL0);
    } else {
        assert(0); // terminate on invalid input
    }

    // this won't be null
    return nextBlock;
}
