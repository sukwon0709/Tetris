#ifndef __LEVEL_H_
#define __LEVEL_H_

#include <iostream>
#include <fstream>
#include <memory>
#include "block.h"
#include "blockFactory.h"
#include "window.h"
#include "types.h"

/*
 * Handles all level related operations
 */
class Level
{
public:
    // only one file read for level0 getNextBlock()
    static const char * fileName;
    // types defining possible levels
    enum LevelType { LVLBEGIN, LVL0 = LVLBEGIN, LVL1, LVL2, LVL3, LVLEND };

    // ctor
    Level();

    /*
     * dispatches to appropriate blockFactory for the current level
     *
     * @return pointer to the newly instantiated block instance
     * @throw FileIOException if file read error for level 0
     */
    Block* getNextBlock();

    /*
     * returns current level
     *
     * @return current level in LevelType type
     */
    LevelType getLevel() const;

    /*
     * returns current score
     *
     * @return current score
     */
    size_t getScore() const;

    /*
     * returns current high score
     *
     * @return current highscore
     */
    size_t getHighScore() const;

    /*
     * updates current/high score when a row in a grid is deleted
     *
     * score += (level+1)^2
     */
    void updateScore();

    /*
     * updates current/high score when a block is completely deleted
     *
     * score += (level of block+1)^2
     * @param b a block which is completely deleted from grid
     *  use the block's level (level when it's created) to update score
     */
    void updateScore(const Block & b);

    // increments current level (doesn't do anything if already at level3)
    void lvlUp();

    // decrements current level (doesn't do anything if already at level0)
    void lvlDown();

    /*
     * called when game is restarted
     *
     * resets all level related data except highscore which is kept for duration
     * of game play
     */
    void reset();

    /*
     * draws level to graphical display
     *
     * @param w Xwindows graphical instance
     */
    void draw(Xwindow& w) const;

    /*
     * output operator for outputing level instance on output stream
     *
     * @param out output stream
     * @param lvl level instance
     * @return output stream
     */
    friend std::ostream & operator<<(std::ostream & out, const Level & lvl);

private:
    /*
     * called internal to Level instance
     *
     * if new score is greater than the current highscore
     * update highscore to the new score
     */
    void updateHighScore();

    LevelType currentLevel;
    std::ifstream file; // sequence.txt for lvl0 block creation
    BlockFactoryPtr blockFactories[LVLEND]; // array of available blockFactories
    size_t score;
    size_t highscore;
};

#endif // __LEVEL_H_
