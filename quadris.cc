#include "quadris.h"
#include "RndNumGenerator.h"
#include "level.h"
#include <iostream>
#include <cassert>

using namespace std;

/*
 * NOTE: please refer to quadris.h for method specific comments
 */

Quadris::Quadris()
: board()
, interpreter()
{}

Quadris& Quadris::getInstance()
{
    // this is not thread-safe
    // however, we don't care because getInstance() is called
    // before another thread is created.
    static Quadris quadris;
    return quadris;
}

void Quadris::setTextMode(bool textMode)
{
    // dynamically create graphical display if not in text mode
    if (!textMode) {
        board.createGUI();
    }
    interpreter.setTextMode(textMode); // sets interpreter to textmode
}

void Quadris::setSeed(uint32_t seed)
{
    // RndNumGenerator is another singleton class handling random number generation
    // there will only be one instance of the class so seed set below will persist
    // until another change of seed
    RndNumGenerator& rndGen = RndNumGenerator::getInstance();
    rndGen.seed(seed); // initializes seed value
}

void Quadris::setVerbose(bool verbose)
{
    // set interpreter to verbose mode
    interpreter.setVerbose(verbose);
}

/*
 * handles tetris part of the game when in tetris mode
 *
 * @param quadris quadris instance
 */
void* Quadris::tetrisMode(void * quadris)
{
    Quadris * q = static_cast<Quadris*>(quadris);
    while (!q->interpreter.isFinished()) {
        int speed = 0;
        switch (q->board.getLevel().getLevel()) {
            case Level::LVL0:
            case Level::LVL1:
                speed = tetrisSpeed;  // 1 sec for every down move
                break;
            case Level::LVL2:
                speed = tetrisSpeed/2; // 0.5 sec for every down move
                break;
            case Level::LVL3:
                speed = tetrisSpeed/4; // 0.25 sec for every down move
                break;
            default: // can't happen
                assert(0);
        }

        // if move's second arg is true, Board::move()
        // will call drop() if the active block can't move down further
        q->board.move(Block::down, true);
        q->interpreter.drawBoard(q->board); // updates text or graphical display
        usleep(speed); // simulates speed of falling active block
    }

    return 0;
}

void Quadris::start(bool tetrisMode)
{
    // if tetris mode, create a thread which handles falling active block
    if (tetrisMode) {
        pthread_create(&tid, NULL, &Quadris::tetrisMode, this);
    }
    interpreter.run(cin, board);
    if (tetrisMode) {
        pthread_join(tid, NULL); // waits until testrisMode thread is terminated
    }
}
