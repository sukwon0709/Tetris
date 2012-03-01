#ifndef __DROP_H_
#define __DROP_H_

#include "command.h"

/*
 * Drop command function object
 *
 * handles dropping of the current active block when user commands 'drop'
 */
class Drop : public Command
{
public:
    Drop()
    : Command("drop")
    {}

    /*
     * handles drop command
     *
     * @param board needs board to handle drop command
     */
    void operator()(Board & board) const;
};

#endif // __DROP_H_
