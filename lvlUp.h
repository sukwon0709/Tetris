#ifndef __LEVELUP_H_
#define __LEVELUP_H_

#include "command.h"

/*
 * LevelUp command function object
 *
 * handles levelup command
 */
class LevelUp : public Command
{
public:
    LevelUp()
    : Command("levelup")
    {}

    /*
     * handles levelup command
     *
     * @param board board dispatches levelup to level instance
     */
    void operator()(Board & board) const;
};

#endif // __LEVELUP_H_
