#ifndef __COMMAND_H_
#define __COMMAND_H_

#include <string>

// forward decl
class Board;

/*
 * abstract class representing Command functor
 */
class Command
{
public:
    /*
     * Constructor
     *
     * @param commandName name of the command instance recognized on command-line
     */
    Command(const std::string & commandName)
    : commandName(commandName)
    {}

    virtual ~Command() {}

    // performs actual command
    virtual void operator()(Board & board) const = 0;

    /*
     * returns currently set commandName for the command instance
     *
     * @return commandName command name of the command instance
     */
    const std::string & getCommandName() const { return commandName; } // inlined because small method

    /*
     * sets commandName of the command instance.
     * this will be used by interpreter when renaming command event is raised by user.
     *
     * @param name new command name
     */
    void setCommandName(const std::string & name) { commandName = name; } // inline because small method

private:
    std::string commandName;
};

#endif // __COMMAND_H_
