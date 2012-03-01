#include "rotateCW.h"
#include "board.h"

/*
 * handles rotating active block clockwise
 */
void RotateCW::operator()(Board & board) const
{
    board.move(Block::CW);
}
