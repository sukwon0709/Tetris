#ifndef __MOVERIGHT_H_
#define __MOVERIGHT_H_

#include "command.h"

/*
 * MoveRight command function object
 *
 * handles moving right active block
 */
class MoveRight : public Command
{
public:
    MoveRight()
    : Command("right")
    {}

    /*
     * handles move right command
     *
     * @param board dispatches move right command to board
     */
    void operator()(Board & board) const;
};

#endif // __MOVERIGHT_H_
