#include "brick.h"

/*
 * NOTE: all the comments explaning methods themselves are written in brick.h
 */

Brick::Brick(bool removed)
: x(0)
, y(0) 
, removed(removed)
{}


int Brick::getX() const {
    return x;
}

int Brick::getY() const {
    return y;
}

bool Brick::active() const {
    return !removed;
}

void Brick::setX(int x) {
    this->x = x;
}

void Brick::setY(int y) {
    this->y = y;
}

void Brick::kill() {
    removed = true;
}
