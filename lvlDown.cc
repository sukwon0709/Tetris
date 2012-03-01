#include "lvlDown.h"
#include "board.h"

/*
 * Handles levelling down
 */
void LevelDown::operator()(Board & board) const
{
    board.levelDown();
}
