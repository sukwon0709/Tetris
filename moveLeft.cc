#include "moveLeft.h"
#include "board.h"

using namespace std;

/*
 * handles moving active block to the left
 */
void MoveLeft::operator()(Board & board) const
{
    board.move(Block::left);
}
