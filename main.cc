#include "quadris.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

/*
 * prints out usage on stderror stream
 * when invalid command-line arguments are specified
 */
void usage()
{
    cerr << "Usage: ./quadris [-text] [-seed xxx] [-verbose]" << endl;
    exit(-1);
}

int main(int argc, char *argv[])
{
    // gets a singleton instance of quadris
    Quadris & quadris = Quadris::getInstance();

    // handles command-line arguments
    bool isTextMode = false;
    bool isSeedSet = false;
    uint32_t seed = 0;
    bool isVerboseMode = false;
    bool isTetris = false;
    for (int i=1; i<argc; ++i) {
        if (strncmp(argv[i], "-text", 5) == 0) {
            isTextMode = true;
        } else if (strncmp(argv[i], "-seed", 5) == 0) {
            if (i == argc-1) {
                usage();
            }
            isSeedSet = true;
            seed = atol(argv[++i]); // seed is unsigned int (use atol instead of atoi)
        } else if (strncmp(argv[i], "-verbose", 8) == 0) {
            isVerboseMode = true;
        } else if (strncmp(argv[i], "-tetris", 7) == 0) {
            isTetris = true;
        }
    }

    // initialize quadris
    quadris.setTextMode(isTextMode);
    if (isSeedSet) {
        quadris.setSeed(seed);
    }
    quadris.setVerbose(isVerboseMode);

    // starts up quadris game
    // if isTertris is true, starts up tetris game
    // otherwise, quadris game is started
    quadris.start(isTetris);

    return 0;
}
