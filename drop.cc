#include "drop.h"
#include "board.h"

/*
 * Handles dropping of active block and updates to next block
 */
void Drop::operator()(Board & board) const
{
    board.drop();
}
