#ifndef __MOVELEFT_H_
#define __MOVELEFT_H_

#include "command.h"

/*
 * MoveLeft comand function object
 *
 * handles moveing left active block
 */
class MoveLeft : public Command
{
public:
    MoveLeft()
    : Command("left")
    {}

    /*
     * handles move left command
     *
     * @param board dispatches move left command to board
     */
    void operator()(Board & board) const;
};

#endif // __MOVELEFT_H_
