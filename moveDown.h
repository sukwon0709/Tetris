#ifndef __MOVEDOWN_H_
#define __MOVEDOWN_H_

#include "command.h"

/*
 * MoveDown command function object
 *
 * handles moving down of active block
 */
class MoveDown : public Command
{
public:
    MoveDown()
    : Command("down")
    {}

    /*
     * handles moving down of active block
     *
     * @param board dispatches move down command to board
     */
    void operator()(Board & board) const;
};

#endif // __MOVEDOWN_H_
