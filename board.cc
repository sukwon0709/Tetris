#include "board.h"
#include "AutoLock.h"
#include "exceptions.h"

using namespace std;

/*
 * NOTE: all the comments explaning methods themselves are written in grid.h
 */

Board::Board()
: activeBlock()
, nextBlock()
, prevNextBlock()
, allBlocks()
, lvl()
, lastMove(Block::invalid)
, theGrid()
, undoing(false)
, mutex(PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP)
, mainWindowPtr()
{
    activeBlock.reset(lvl.getNextBlock());
    for (int i=0; i<Grid::yBuffer; ++i) {
        move(Block::down);
    }
    theGrid.drawActiveBlock(*activeBlock);
    nextBlock.reset(lvl.getNextBlock());
}

Board::~Board()
{
    pthread_mutex_destroy(&mutex);
}

void Board::clearGrid() {
    AutoLock l(&mutex);
    theGrid.clear();
}

void Board::createGUI() {
    mainWindowPtr.reset(new Xwindow(240, 460));
    mainWindowPtr->fillRectangle(0, 0 , 240, 460, Xwindow::Black);
    mainWindowPtr->fillRectangle(19, 79, 10*20+2, 18*20+2, Xwindow::White);
    mainWindowPtr->fillRectangle(20, 80, 10*20, 18*20, Xwindow::Black);
    blockWindowPtr.reset(new Xwindow(160, 140));
    blockWindowPtr->fillRectangle(0, 0, 160, 140, Xwindow::Black);
    blockWindowPtr->fillRectangle(19, 39, 122, 82, Xwindow::White);
    blockWindowPtr->fillRectangle(20, 40, 120, 80, Xwindow::Black);
    blockWindowPtr->drawString(20, 30, "Next Block", Xwindow::White);
    // smallWindow creation
}


void Board::checkValidity() {
    AutoLock l(&mutex);
    if (theGrid.validMove()) {
        undoing = false;
    } else {
        undoMove();
    }
}

void Board::undoMove() {
    AutoLock l(&mutex);
    undoing = true;
    switch (lastMove) {
        case Block::up: move(Block::down); break;
        case Block::down: move(Block::up); break;
        case Block::left: move(Block::right); break;
        case Block::right: move(Block::left); break;
        case Block::CW: move(Block::CCW); break;
        case Block::CCW: move(Block::CW); break;
        default: // invalid
            break;
    }
}

void Board::levelUp() {
    AutoLock l(&mutex);
    lvl.lvlUp();
}

void Board::levelDown() {
    AutoLock l(&mutex);
    lvl.lvlDown();
}

void Board::move(Block::move_t dir, bool tetris) {
    AutoLock l(&mutex);
    if (!undoing) {
        theGrid.removeActiveBlock(*activeBlock);
    }
    activeBlock->move(dir);
    lastMove = dir;
    theGrid.drawActiveBlock(*activeBlock);
    checkValidity();

    // cannot move down further, call drop automatically
    if (tetris && lastMove == Block::up) {
        drop();
    }
}

void Board::updateScores() {
    AutoLock l(&mutex);
    bool cleared = false;
    for (int i = Block::firstY-Grid::yBuffer; i >= 0; --i) {
        cleared = theGrid.rowFull(i);
        if (!cleared) continue;                 // if this row doesn't need
                                                // to be cleared, go to next row
        
        lvl.updateScore();                      // score update for cleared ROW
        for (vector<BlockPtr>::iterator it = allBlocks.begin(); it != allBlocks.end(); /* done with all blocks */ ) {
            for (int j = 0; j < 4; ++j) {
                int x = (*it)->getCoords(j).first;
                int y = (*it)->getCoords(j).second;
                if (y > i) {
                    (*it)->setCoords(j, x, y-1);
                    continue;       // move down all Bricks above the cleared row
                } else if (y < i) {
                    continue;       // if not the Brick at row i, go to next brick
                }
                (*it)->kill(j);     // if Brick was at row i, remove from Grid
            }
            if ((*it)->removed()) { // checks if whole Block has been removed from Grid
                lvl.updateScore(*(*it));   // score update for cleared BLOCK
                it = allBlocks.erase(it);  // removes dead Block from the Vector
            } else {
                ++it;
            }
        }
    }
}
			
void Board::drop() {

    // 1. move activeBlock as far down as possible;
    // 2. check for rows cleared, update scores
    // 3. retire activeBlock, replace with nextBlock;
    // 4. get a new nextBlock;
    // 5. update (draw) theGrid with the new activeBlock;

    AutoLock l(&mutex);

    while (lastMove != Block::up) {         // 1
        move(Block::down);
    }
    lastMove = Block::down;                 // to prevent conflict with new activeBlock
    allBlocks.push_back(activeBlock);
    updateScores();                         // 2
    activeBlock = nextBlock;                // 3
    for (int i=0; i<Grid::yBuffer; ++i) {
        move(Block::down);
    }

    try {
        nextBlock.reset(lvl.getNextBlock());    // 4
    } catch (FileIOException & e) {
        // EOF or read error occurred for level0 getNextBlock()
        // restart game
        restart();
    }

    // redraw everything (5)
    theGrid.clear();
    theGrid.drawActiveBlock(*activeBlock);
    theGrid.draw(allBlocks);

    if (lastMove == Block::up) {
        restart();
    }
}
	
void Board::restart() {
    AutoLock l(&mutex);

    clearGrid();
    lvl.reset();
    allBlocks.clear();
    activeBlock.reset(lvl.getNextBlock());
    nextBlock.reset(lvl.getNextBlock());
    for (int i=0; i<Grid::yBuffer; ++i) {
        move(Block::down);
    }
    theGrid.drawActiveBlock(*activeBlock);
}

const Level& Board::getLevel() const {
    return lvl;
}

const Grid& Board::getGrid() const {
    return theGrid;
}

const Block& Board::getNextBlock() const {
    return *nextBlock;
}

void Board::draw() {
    AutoLock l(&mutex);

    lvl.draw(*mainWindowPtr);
    theGrid.draw(*mainWindowPtr);

    // only redraw nextBlock when next block changed from last draw
    if (nextBlock.get() != prevNextBlock.get()) {
        nextBlock->draw(*blockWindowPtr);
    }
    prevNextBlock = nextBlock;
}

ostream& operator<<(ostream &out, const Board& b) {
    AutoLock l(&b.mutex);

    out << b.getLevel() << endl;
    out << b.getGrid() << endl;
    out << "Next:\n" << b.getNextBlock() << endl;
    out << endl;
    return out;
}
