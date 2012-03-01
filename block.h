#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "brick.h"
#include <utility>
#include "window.h"
#include <iostream>

/*
 * Abstract class for all 7 types of blocks
 *
 * A Block consists of 4 Bricks
 */
 
class Block
{
public:
    // class-specific constants that are static and of integral type
    // does not require a definition as long as their address are not taken (Item 2, Effective C++)
    static const int firstX = 0;
    static const int firstY = 17;

    // define types
    enum move_t {invalid, up, down, left, right, CW, CCW};
    enum block_t {I, J, L, O, S, Z, T};

    Block(block_t t, int lvl); // ctor
    virtual ~Block() {} // virtual dtor

    // accessors
    block_t getType() const;
    int getCreatedLevel() const;
    std::pair<int, int> getCoords(int) const;   // get coordinates of a particular Brick
    bool removed() const;   // checks if whole Block (all 4 Bricks) is out of Grid
    bool active(int i) const;   // checks if a particular Brick is still in Grid
    
    // setters
    void setCoords(int, int, int);  // sets coordinates of a particular Brick
    void kill(int);                 // kill a particular Brick
    void move(move_t dir);    // moves and rotations
    
    // pure virtual functions
    virtual void draw(std::ostream & out) const = 0;    // for text output
    virtual void draw(Xwindow& w) const = 0;    // for Xwindow drawing
    virtual char getSymbol() const = 0; // to get Block type in char format

    friend std::ostream & operator<<(std::ostream & out, const Block & b);

private:
    block_t type;
    Brick bricks[4];    // each Block contains 4 Bricks
    int createdLevel;   // for scoring purposes
    bool isRemoved;     // set to true when all 4 Bricks are killed

    void translate(move_t dir); // moves (up, down, left, right)    
    void rotate(move_t dir);    // rotation function

};

#endif
