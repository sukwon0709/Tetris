#ifndef __BOARD_H__
#define __BOARD_H__

#include "block.h"
#include "grid.h"
#include "level.h"
#include "types.h"
#include "window.h"
#include <iostream>
#include <memory> // for shared_ptr c++0x
#include <vector>
#include <pthread.h>

class Board
{
public:
    Board();
    ~Board();

    // setters
    void levelUp();
    void levelDown();
    void move(Block::move_t dir, bool tetris=false);	// moves and rotations
    void drop();
    void restart();	// calls Level::reset() and clearGrid()
    
    // accessors
    const Level& getLevel() const;

    void createGUI(); // constructs Xwindow
    void draw(); // draws graphical output

    friend std::ostream& operator<<(std::ostream &out, const Board &b);

private:
    BlockPtr activeBlock;
    BlockPtr nextBlock;
    BlockPtr prevNextBlock;  // compare when drawing nextBlock on graphical display
                             // to only draw when prevNextBlock != nextBlock
    std::vector<BlockPtr> allBlocks;
    Level lvl;
    Block::move_t lastMove; // for purpose of undoing invalid moves
    Grid theGrid;           // actual playing field
    bool undoing;			// see if we are undoing a move; defaults as false

    const Grid & getGrid() const;
    const Block& getNextBlock() const;
    
    mutable pthread_mutex_t mutex;

    XwindowPtr mainWindowPtr;
    XwindowPtr blockWindowPtr;

    // clears all Bricks from the Grid; called by restart()
    void clearGrid();
    // checks with Grid if the latest move is valid; undo the move if not; called by move()
    void checkValidity();	
    // undo the latest move done on activeBlock if it was an invalid move; called by checkValidity()
    void undoMove();
    // checks for scoring criteria (row ; called by drop() 
    void updateScores();
};

#endif
