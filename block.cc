#include <algorithm>
#include <string>
#include "block.h"    

using namespace std;

/*
 * NOTE: all the comments explaning methods themselves are written in block.h
 */

Block::Block(block_t t, int lvl)
: type(t)
, createdLevel(lvl)
, isRemoved(false)
{}

Block::block_t Block::getType() const {
    return type;
}

int Block::getCreatedLevel() const {
    return createdLevel;
}

void Block::rotate(move_t dir) {
    if (type == O) return;  // no need to rotate
    
    int x,y;                // use to hold coordinates value as needed
    int allX[4],allY[4];    // to hold all x and y values of the Bricks
    int oldRefX,oldRefY;    // point of reference before rotation
    int newRefX,newRefY;    // point of reference after rotation
    int k;                  // for slight change in algorithm between CW and CCW
    
    // get all x and y coordinates in separate arrays
    for (int i = 0; i < 4; i++) {
        allX[i] = bricks[i].getX();
        allY[i] = bricks[i].getY();
    }

    // for clockwise rotation
    // old reference point is lower-right corner
    // new reference point is lower-left corner
    if (dir == CW) {
        oldRefX = *max_element(allX,allX+4);
        oldRefY = *min_element(allY,allY+4);
        newRefX = *min_element(allX,allX+4);
        newRefY = oldRefY;
        k = 1;
    }
    // for counter-clockwise rotation
    // old reference point is top-left corner
    // new reference point is lower-left corner
    else if (dir == CCW) {
        oldRefX = *min_element(allX,allX+4);
        oldRefY = *max_element(allY,allY+4);
        newRefX = oldRefX;
        newRefY = *min_element(allY,allY+4);
        k = -1;
    }
    
    // updating the Bricks with new coordinates
    for (int i = 0; i < 4; i++) {
        x = bricks[i].getX();
        y = bricks[i].getY();
        bricks[i].setX(newRefX - k * (oldRefY - y));
        bricks[i].setY(newRefY + k * (oldRefX - x));
    }
}

void Block::move(move_t dir) {
    switch(dir) {
        case up:
        case down:
        case left:
        case right:
            translate(dir); break;
        case CW:
        case CCW:
            rotate(dir); break;
        default: // invalid
            break;
    }
}

void Block::translate(move_t dir) {
    for (int i=0; i<4; i++) {
        switch (dir) {
            case up:    bricks[i].setY(bricks[i].getY() + 1); break;    // to reverse invalid down moves
            case down:  bricks[i].setY(bricks[i].getY() - 1); break;
            case left:  bricks[i].setX(bricks[i].getX() - 1); break;
            case right: bricks[i].setX(bricks[i].getX() + 1); break;
            default: break;
        }
    }
}

pair<int, int> Block::getCoords(int i) const {
    pair<int, int> t(bricks[i].getX(), bricks[i].getY());
    return t;
}

void Block::setCoords(int i, int x, int y) {
    bricks[i].setX(x);
    bricks[i].setY(y);
}

// kills a particular brick, and checks if the whole block has been removed
void Block::kill(int i) {
    bricks[i].kill();
    isRemoved = true;
    for (int j = 0; j < 4; j++) {
        if (bricks[j].active()) {
            isRemoved = false;
            break;
        }
    }
}

bool Block::removed() const {
    return isRemoved;
}

bool Block::active(int i) const{
    // throw exception if outofbound
    return bricks[i].active();
}

ostream & operator<<(ostream & out, const Block & b) {
    b.draw(out);
    return out;
}
