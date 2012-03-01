#ifndef __RESTART_H_
#define __RESTART_H_

#include "command.h"

/*
 * Restart command function object
 *
 * handles restarting the quadris game
 */
class Restart : public Command
{
public:
    Restart()
    : Command("restart")
    {}

    /*
     * handles restart command
     *
     * @param board dispatches restart command to board
     */
    void operator()(Board & board) const;
};

#endif // __RESTART_H_
