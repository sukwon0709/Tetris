#ifndef __GRID_H__
#define __GRID_H__

#include "block.h"
#include "brick.h"
#include "types.h"
#include "window.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Grid {
public:
    // class-specific constants that are static and of intergral type
    // does not require a definition as long as their address is not taken (Item2, Effective C++)
    static const int minX = 0;
    static const int minY = 0;
    static const int maxX = 10;
    static const int maxY = 15;
    static const int yBuffer = 3;
    static const int brickSize = 20;

    Grid();                     // ctor; all undesignated Bricks (calls clear())
    void clear();               // remove all Bricks designations
    void draw(const std::vector<BlockPtr> & blocks);            // draws ALL active Bricks onto actualGrid
    void removeActiveBlock(const Block& b);           // undraw the activeBlock (from actualGrid)
    void drawActiveBlock(const Block& b);             // draws the activeBlock (onto actualGrid)
    bool validMove() const;
    bool rowFull(int i);                              // returns true if row i is completely filled
    
    void draw(Xwindow& w);                            // for Xwindow output
    
    friend std::ostream& operator<<(std::ostream &out, const Grid &g);

private:
    char actualGrid[maxY+yBuffer+1][maxX];	// +1 to prevent oob
    char oldGrid[maxY+yBuffer+1][maxX];     // backup of actualGrid (for graphical optimization purposes)
    bool updateOK;                          // sets to true if a valid move was called (and executed); false o/w
    void backupGrid();                      // saves a copy of actualGrid to oldGrid

    void prelimCheck(const Block &b);                   // checks if a move is valid and sets field updateOK accordingly
    void updateActiveBlock(const Block &b, const std::string & mode);  // actual updating code,
                                                                       // called by removeActiveBlock() and drawActiveBlock()
};

#endif
