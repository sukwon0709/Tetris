#ifndef __ROTATECCW_H_
#define __ROTATECCW_H_

#include "command.h"

/*
 * Rotate counterclockwise function object
 *
 * handles rotating active block counterclockwise
 */
class RotateCCW : public Command
{
public:
    RotateCCW()
    : Command("counterclockwise")
    {}

    /*
     * handles rotate counterclockwise command
     *
     * @param board dispatches board's rotate method
     */
    void operator()(Board & board) const;
};

#endif // __ROTATECCW_H_
