#include "rotateCCW.h"
#include "board.h"

/*
 * handles rotating active block counter clockwise 
 */
void RotateCCW::operator()(Board & board) const
{
    board.move(Block::CCW);
}
