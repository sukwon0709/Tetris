#include "level.h"
#include <iomanip>
#include <sstream>

#include "blockFactoryLevel0.h"
#include "blockFactoryLevel1.h"
#include "blockFactoryLevel2.h"
#include "blockFactoryLevel3.h"

using namespace std;

/*
 * NOTE: all the comments explaning methods themselves are written in level.h
 */

// defines static variable fileName to sequence.txt (fixed for the program)
const char * Level::fileName = "sequence.txt";

Level::Level()
: currentLevel(LVL1) // start at level1
, file(fileName)
, score(0)
, highscore(0)
{
    // initializes array of available block factories
    // level will call appropriate block factory's getNextBlock()
    // to instantiate next block for play
    blockFactories[LVL0].reset(new BlockFactoryLevel0(file));
    blockFactories[LVL1].reset(new BlockFactoryLevel1());
    blockFactories[LVL2].reset(new BlockFactoryLevel2());
    blockFactories[LVL3].reset(new BlockFactoryLevel3());
}

Block* Level::getNextBlock()
{
    return blockFactories[currentLevel]->getNextBlock();
}

Level::LevelType Level::getLevel() const
{
    return currentLevel;
}

size_t Level::getScore() const
{
    return score;
}

size_t Level::getHighScore() const
{
    return highscore;
}

void Level::updateScore()
{
    // static_cast to int to perform update score calculation
    int lvl = static_cast<int>(currentLevel);
    score += (lvl+1)*(lvl+1);
    updateHighScore();
}

void Level::updateScore(const Block & b)
{
    int lvl = b.getCreatedLevel();
    score += (lvl+1)*(lvl+1);
    updateHighScore();
}

void Level::updateHighScore()
{
    if (highscore < score) {
        highscore = score;
    }
}

void Level::lvlUp()
{
    // checks if already at highest level
    if (currentLevel == LVL3) return;
    int lvl = static_cast<int>(currentLevel) + 1;
    currentLevel = static_cast<LevelType>(lvl);
}

void Level::lvlDown()
{
    // checks if already at lowest level
    if (currentLevel == LVL0) return;
    int lvl = static_cast<int>(currentLevel) - 1;
    currentLevel = static_cast<LevelType>(lvl);
}

void Level::reset()
{
    score = 0;
    currentLevel = LVL1; // always restart at level1
    file.close();
    file.open(fileName); // reinitialize filestream
}

void Level::draw(Xwindow& w) const
{
    w.fillRectangle(0, 0, 240-1, 80-1, Xwindow::Black);

    // use ostringstream to construct string to display on graphics
    ostringstream os;
    os << "Level:" << setw(10) << static_cast<int>(currentLevel);
    w.drawString(20, 20, os.str(), Xwindow::White);
    os.str(""); // reset

    os << "Score:" << setw(10) << score;
    w.drawString(20, 40, os.str(), Xwindow::White);
    os.str(""); // reset

    os << "Hi Score:" << setw(7) << highscore;
    w.drawString(20, 60, os.str(), Xwindow::White);
}

ostream& operator<<(ostream & out, const Level & lvl)
{
    out << "Level:" << setw(10) << static_cast<int>(lvl.getLevel()) << endl;
    out << "Score:" << setw(10) << lvl.getScore() << endl;
    out << "Hi Score:" << setw(7) << lvl.getHighScore();

    return out;
}
