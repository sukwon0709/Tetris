#include "grid.h"

using namespace std;

/*
 * NOTE: all the comments explaning methods themselves are written in grid.h
 */

Grid::Grid() {
    clear();
}

void Grid::prelimCheck(const Block& b) {
    int x,y;
    updateOK = true;
    for(int i = 0; i < 4; i++) {
        x = b.getCoords(i).first;
        y = b.getCoords(i).second;
        if (x < minX || y < minY || x >= maxX || actualGrid[y][x] != ' ') {
            updateOK = false;
            break;
        }   // if out of bounds or overlap
    }
}

void Grid::updateActiveBlock(const Block& b, const string& mode) {
    int x,y;
    prelimCheck(b);
    for (int i = 0; i < 4; i++) {
        x = b.getCoords(i).first;
        y = b.getCoords(i).second;
        if (mode == "draw") {
            if (updateOK) {
                actualGrid[y][x] = b.getSymbol();
            }
        } else if (mode == "remove") {
            actualGrid[y][x] = ' ';
        }
    }
}

void Grid::clear() {
    for (int y = maxY+yBuffer; y > minY; y--) {
        for (int x = minX; x < maxX; x++) {
            actualGrid[y-1][x] = ' ';
        }   // for y
    }   // for x
}
    
void Grid::draw(const vector<BlockPtr> & blocks) {
    int x,y;
    char type;
    vector<BlockPtr>::const_iterator it;
    vector<BlockPtr>::const_iterator itEnd = blocks.end();
    for (it = blocks.begin(); it != itEnd; ++it) {
        type = (*it)->getSymbol();
        for (int j = 0; j < 4; j++) {
            x = (*it)->getCoords(j).first;
            y = (*it)->getCoords(j).second;
            if ((*it)->active(j)) {
                actualGrid[y][x] = type;
            }   // if
        }   // for j
    }   // for it
}

bool Grid::validMove() const
{
    return updateOK;
}

void Grid::removeActiveBlock(const Block & b) {
    updateActiveBlock(b, "remove");
}

void Grid::drawActiveBlock(const Block & b) {
    updateActiveBlock(b, "draw");
}

bool Grid::rowFull(int i) {
    bool full = true;
    int x = 0;
    while (x < maxX && full) {
        if (actualGrid[i][x] == ' ') full = false;
        x++;
    }
    return full;
}

void Grid::draw(Xwindow& w) {
    int startingX = brickSize * 1;
    int startingY = brickSize * 4;
    int xPixel, yPixel;
    int brickFill = brickSize - 1;
    char type;
    char oldType;
    for (int y = maxY+yBuffer; y > minY; y--) {
        for (int x = minX; x < maxX; x++) {
            type = actualGrid[y-1][x];
            oldType = oldGrid[y-1][x];
            if (oldType == type) continue;      // FOR GRAPHICAL OPTIMIZATION
            xPixel = startingX + x * brickSize + 1;
            yPixel = startingY + (Block::firstY + 1 - y) * brickSize + 1;
            switch (type) {
                case ' ': w.fillRectangle(xPixel, yPixel, brickFill, brickFill, Xwindow::Black);
                    break;
                case 'I': w.fillRectangle(xPixel, yPixel, brickFill, brickFill, Xwindow::Red);
                    break;
                case 'J': w.fillRectangle(xPixel, yPixel, brickFill, brickFill, Xwindow::Magenta);
                    break;
                case 'L': w.fillRectangle(xPixel, yPixel, brickFill, brickFill, Xwindow::Cyan);
                    break;
                case 'O': w.fillRectangle(xPixel, yPixel, brickFill, brickFill, Xwindow::Blue);
                    break;
                case 'S': w.fillRectangle(xPixel, yPixel, brickFill, brickFill, Xwindow::Orange);
                    break;
                case 'Z': w.fillRectangle(xPixel, yPixel, brickFill, brickFill, Xwindow::Green);
                    break;
                case 'T': w.fillRectangle(xPixel, yPixel, brickFill, brickFill, Xwindow::Brown);
                    break;
            }
        }
    }
    backupGrid();
}

void Grid::backupGrid() {
    for (int y = maxY+yBuffer; y > minY; y--) {
        for (int x = minX; x < maxX; x++) {
            oldGrid[y-1][x] = actualGrid[y-1][x];
        }
    }
}

ostream& operator<<(ostream &out, const Grid &g) {
    for (int i = 0; i < Grid::maxX; i++) {
        out << '-';
    }
    out << endl;
    for (int y = Grid::maxY+Grid::yBuffer; y > Grid::minY; y--) {
        for (int x = Grid::minX; x < Grid::maxX; x++) {
            out << g.actualGrid[y-1][x];
        }   // for x
        out << endl;
    }   // for y
    for (int i = 0; i < Grid::maxX; i++) {
        out << '-';
    }   // for i
    return out;
}