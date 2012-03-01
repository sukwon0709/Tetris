#ifndef __LEVELDOWN_H_
#define __LEVELDOWN_H_

#include "command.h"

/*
 * LevelDown command function object
 *
 * handles leveldown command
 */
class LevelDown : public Command
{
public:
    LevelDown()
    : Command("leveldown")
    {}

    /*
     * handles leveldown command
     *
     * @param board board dispatches leveldown to level instance
     */
    void operator()(Board & board) const;
};

#endif // __LEVELDOWN_H_
