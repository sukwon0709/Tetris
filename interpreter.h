#ifndef __INTERPRETER_H_
#define __INTERPRETER_H_

#include "board.h"
#include "command.h"
#include "types.h"

#include <functional>
#include <iostream>
#include <set>
#include <string>

// defines ordering for CommandSet
struct CommandLess : public std::binary_function<CommandPtr, CommandPtr, bool>
{
public:
    bool operator()(const CommandPtr & cmd1, const CommandPtr & cmd2) const;
};

/*
 * Command-Line interpreter
 *
 * accepts user input commands on command-line interface
 * and handles appropriate actions by given commands.
 */
class Interpreter
{
public:
    /*
     * Constructor
     *
     * @param verbose interpreter will be set on verbose mode if true; default is false
     */
    Interpreter(bool verbose=false);

    /*
     * starts up interpreter instances
     *
     * @param in input stream for listening for user commands
     * @param board needs board instance to dispatch appropriate commands to it
     */
    void run(std::istream & in, Board & board);

    /*
     * sets text mode
     *
     * @param textMode if true, text only mode; false, text and graphical mode
     */
    void setTextMode(bool textMode);

    /*
     * sets verbose mode
     *
     * @param verbose if true, verbose mode for interpreter (autocompletion when ambiguous command is given)
     * if false, autocompletion disabled
     */
    void setVerbose(bool verbose);

    /*
     * draws board on text/graphical display
     *
     * @param board will draw this board
     */
    void drawBoard(Board & board) const;

    /*
     * alerts other component is interpreter encountered EOF (its done accepting inputs)
     *
     * this will be a control for ending tetris thread if run in tetris mode
     * @returns true if saw I/O error (e.g. EOF), false if othersiwe
     */
    bool isFinished() const;

private:
    /*
     * parses multiplier if given as part of a user command
     *
     * @param command command to parse multiplier from
     * @return multiplier value
     */
    static int getMultiplier(std::string & command);

    /*
     * separately from Command function object hierarchy, this method
     * handles rename command. It's handled separate from other commands
     * and different ruls apply
     * (i.e. rename command won't be able to change it's name)
     * how to use:
     * i.e. rename clockwise cw
     *
     * @param in input stream which accepts rename command
     * @return true if rename completed successfully, false if renaming failed
     * because there's already another command with same name.
     */
    bool handleRenameCommand(std::istream & in);

    bool textMode;
    bool verbose;
    volatile bool finishedGame; // declared as volatile to prevent this being stored to a cache
                                // do not require locking because it's only changed once
                                // by interpreter thread (main thread) and read from tetris thread

    typedef std::set<CommandPtr, CommandLess> CommandSet;
    CommandSet commandSet; // set of command function objects
};

#endif // __INTERPRETER_H_
