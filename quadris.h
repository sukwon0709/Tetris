#ifndef __QUADRIS_H_
#define __QUADRIS_H_

#include "board.h"
#include "interpreter.h"
#include <pthread.h>

/*
 * Quadris class
 *
 * the class encapsulates board and interpreter which is required
 * to run quadris and simply calling Quadris::run() will do the job.
 *
 * The class itself is designed as a singleton instance which is to prohibit
 * users from creating multiple instances of Quadris game which does not make sense
 * in a single application.
 *
 * Normally, quadris dispathes to Interpreter::run() which starts accepting user input
 * and runs the game.
 * However, if tetris mode is set, it will create another thread which calls Quadris::tetrisMode()
 * which automatically moves down active blocks with predefined speed depending on the level of the game
 */
class Quadris
{
public:
    /*
     * returns a single instance of Quadris throughout the lifetime of application
     *
     * @return a single instance of Quadris
     */
    static Quadris& getInstance();

    /*
     * starts up quadris game
     *
     * @param tetris if true, run tetris game; otherwise run quadris game
     */
    void start(bool tetris=false);

    /*
     * sets text mode
     *
     * @param textMode if true, runs text only mode; otherwise text/graphical mode
     */
    void setTextMode(bool textMode);

    /*
     * sets seed value
     *
     * @param seed random number generation for creating next block will use this value
     */
    void setSeed(uint32_t seed);

    /*
     * sets verbose mode
     *
     * @param verbose if true, interpreter will do autocompletion of commands
     */
    void setVerbose(bool verbose);

private:
    // enforces singleton by defining constructor
    // copy ctor, and assignment operator as private
    // copy ctor and assignment operator is unimplemented
    Quadris();
    Quadris(const Quadris & q);
    Quadris& operator=(const Quadris & q);

    // static method responsible for running tetrisMode
    // this will periodically move down active block and calls drop
    // if the block cannot move down further
    static void* tetrisMode(void * q);

    // Quadris is composited of board and interpreters to run the game
    Board board;
    Interpreter interpreter;

    static const int tetrisSpeed = 1000000; // default speed of 1 sec per moving block down

    // will only be used in tetris mode (tetris mode thread id)
    pthread_t tid;
};

#endif // _QUADRIS_H_
