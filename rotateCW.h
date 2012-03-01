#ifndef __ROTATECW_H_
#define __ROTATECW_H_

#include "command.h"

/*
 * Rotate clockwise command function object
 *
 * handles rotating active block clockwise
 */
class RotateCW : public Command
{
public:
    RotateCW()
    : Command("clockwise")
    {}

    /*
     * handles rotate clockwise command
     *
     * @param board dispatches board's rotate method
     */
    void operator()(Board & board) const;
};

#endif // __ROTATECW_H_
