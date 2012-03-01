#include "lvlUp.h"
#include "board.h"

/*
 * handles levelling up
 */
void LevelUp::operator()(Board & board) const
{
    board.levelUp();
}
