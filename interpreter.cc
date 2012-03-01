#include "interpreter.h"

#include <cassert>
#include <string>
#include <vector>
#include <utility>

#include "moveLeft.h"
#include "moveRight.h"
#include "moveDown.h"
#include "rotateCW.h"
#include "rotateCCW.h"
#include "drop.h"
#include "lvlUp.h"
#include "lvlDown.h"
#include "restart.h"

using namespace std;

/*
 * NOTE: all the comments explaning methods themselves are written in interpreter.h
 */

// orders by command names in alphabetical order
bool CommandLess::operator()(const CommandPtr & cmd1, const CommandPtr & cmd2) const
{
    return (cmd1->getCommandName() < cmd2->getCommandName());
}

Interpreter::Interpreter(bool verbose)
: textMode(false)
, verbose(verbose)
, finishedGame(false)
{
    // populate command set with already known/required to support commands
    commandSet.insert(CommandPtr(new MoveLeft()));
    commandSet.insert(CommandPtr(new MoveRight()));
    commandSet.insert(CommandPtr(new MoveDown()));
    commandSet.insert(CommandPtr(new RotateCW()));
    commandSet.insert(CommandPtr(new RotateCCW()));
    commandSet.insert(CommandPtr(new Drop()));
    commandSet.insert(CommandPtr(new LevelUp()));
    commandSet.insert(CommandPtr(new LevelDown()));
    commandSet.insert(CommandPtr(new Restart()));

    // other commands to come
    // if other commands are implemented, just include here
    // and interpreter will know how to handle
    // note: command names should not conflict! if they do insert wil fail.
}

int Interpreter::getMultiplier(string & command)
{
    int i=0, mult = 1; // run once if multiplier is missing
    int length = command.size();

    // determines number of digits of multiplier
    while (i < length && command[i] >= '0' && command[i] <= '9') {
        i++;
    }

    // reads off multiplier
    if (i > 0) {
        mult = atoi(command.substr(0, i).c_str());
    }
    // strips out multiplier from command received
    command = command.substr(i);

    return mult;
}

void Interpreter::setTextMode(bool textMode)
{
    this->textMode = textMode;
}

void Interpreter::setVerbose(bool verbose)
{
    this->verbose = verbose;
}

bool Interpreter::handleRenameCommand(istream & in)
{
    bool success = false;

    // parses command to change, new command name
    string origCmd, newCmd;
    in >> origCmd >> newCmd;

    /*
     * iterates over commandset and look for the command to change
     * if name matches, try changing name by
     * 1) remove command from set
     * 2) changes command name
     * 3) inserts back to set
     * to preserve set ordering
     * if insert succeeds, okay; if fails it means there's already a command
     * with new command name. Hence reverts back to the old command name.
     */
    for (CommandSet::iterator it = commandSet.begin(); it != commandSet.end(); /* code below will handle */) {
        const string & cmdName = (*it)->getCommandName();

        // found a command to change it's name
        if (origCmd == cmdName) {
            // remove the command and insert the command with new name (preserve set ordering)
            CommandPtr cmdPtr = (*it); // prevent destructor from being run by sharing ownership
            commandSet.erase(it++);
            cmdPtr->setCommandName(newCmd);
            pair<CommandSet::iterator, bool> result = commandSet.insert(cmdPtr);

            // whoops, insert failed!
            // revert back to previous command
            if (!result.second) {
                // there's a command name conflict! (revert back to old command name)
                cmdPtr->setCommandName(origCmd);
                pair<CommandSet::iterator, bool> result = commandSet.insert(cmdPtr);
                // this should not get printed
                if (verbose) {
                    cerr << "Failed to rename command " << origCmd << " to " << newCmd << endl;
                }
                assert(result.second); // failed to revert to old command!
            }
            success = result.second;
            break;
        } else {
            ++it;
        }
    }
    return success;
}

void Interpreter::drawBoard(Board & board) const
{
    // text display is always enabled
    cout << board;
    if (!textMode) {
        // if not in text mode, draw graphically, too
        board.draw();
    }
}

void Interpreter::run(istream & in, Board & board)
{
    drawBoard(board);

    string command;
    while (in >> command)
    {
        // handles rename command
        // rename command is fixed (meaning rename command's name won't change)
        // this is something we have constraint to make the functionality
        // available with our current design
        if (command == "rename") {
            handleRenameCommand(in);
            drawBoard(board);
            continue; // no point in executing code below
        }

        int multiplier = getMultiplier(command);

        // for autocompletion feature, save all partially matching commands (ambiguous)
        // to a temporary vector of commands
        // i.e. when d is input, store, down, drop in the vector
        CommandSet::iterator it;
        CommandSet::iterator itEnd = commandSet.end();
        vector<CommandPtr> matchedCommands;
        for (it = commandSet.begin(); it != itEnd; ++it) {
            const string & commandName = (*it)->getCommandName();
            if (commandName.substr(0, command.length()) == command) {
                // matched! keep track for verbose mode
                matchedCommands.push_back(*it);
            }
        }

        // the command is ambiguous
        if (matchedCommands.size() > 1) {
            cout << "Command is ambiguous" << endl;
            // extra-feature: when verbose mode is true
            // prints out autocompletion of possible commands the user might have meant
            if (verbose) {
                cout << "Possible commands are:";
                for (size_t i=0; i<matchedCommands.size(); ++i) {
                    cout << " " << matchedCommands[i]->getCommandName();
                }
                cout << endl;
            }
            continue;
        } else if (matchedCommands.size() == 1) {
            // command is not ambiguous and got matched
            // runs command for multiplier times
            for (int i=0; i<multiplier; ++i) {
                (*matchedCommands[0])(board);
            }
        }

        // always draw text/graphical display after each command
        drawBoard(board);
    }

    // set to true if interpreter ends accepting user input
    // tetris thread will check for the condition to exit itself
    finishedGame = true;
}

bool Interpreter::isFinished() const
{
    return finishedGame;
}
