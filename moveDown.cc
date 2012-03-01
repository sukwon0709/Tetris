#include "moveDown.h"
#include "board.h"

/*
 * handles moving down of current active block
 */
void MoveDown::operator()(Board & board) const
{
    board.move(Block::down);
}
