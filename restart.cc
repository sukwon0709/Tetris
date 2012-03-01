#include "restart.h"
#include "board.h"

/*
 * handles restart of the quadris game
 */
void Restart::operator()(Board & board) const
{
    board.restart();
}
