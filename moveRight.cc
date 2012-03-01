#include "moveRight.h"
#include "board.h"

/*
 * handles moving active block to the right
 */
void MoveRight::operator()(Board & board) const
{
    board.move(Block::right);
}
