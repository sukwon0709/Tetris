#ifndef __BRICK_H__
#define __BRICK_H__

/*
 * The fundamental part that makes up a Block
 *
 * 4 Bricks make up a Block
 */

class Brick { 
    int x,y;         // coordinates of the Brick in Grid
    bool removed;    // defaults to false; set to true if Brick is no longer in Grid

public:
    Brick(bool removed = false);    // defaults removed to false

    // accessors
    int getX() const;
    int getY() const;
    bool active() const;            // returns true if Brick is still in Grid

    // setters
    void setX(int x);
    void setY(int y);
    void kill();                    // called when Brick is removed from Grid;
                                    // sets removed to true
};

#endif
