#ifndef __RNDNUMGENERATOR_H_
#define __RNDNUMGENERATOR_H_

#include "PRNG.h"

/*
 * Wrapper to PRNG (pseudo-random number generator class)
 *
 * the class is implemented as a singleton which provides
 * uniformed random numbers to simulate probability model
 * for getNextBlock() for each level
 */
class RndNumGenerator
{
public:
    /*
     * returns a single instance of RndNumGenerator
     *
     * @return a single RndNumGenerator instance
     */
    static RndNumGenerator& getInstance();

    /*
     * updates seed value
     *
     * @param s new seed
     */
    void seed( uint32_t s );

    /*
     * generates random number between [0, UINT_MAX]
     *
     * @return random number
     */
    uint32_t operator()();

    /*
     * generates random number between [0, u]
     *
     * @return random number
     */
    uint32_t operator()( uint32_t u );

    /*
     * generates random number between [l, u]
     *
     * @return random number
     */
    uint32_t operator()( uint32_t l, uint32_t u );

private:
    // private ctor to prohibit users from creating class instances directly
    RndNumGenerator();
    RndNumGenerator(const RndNumGenerator & rndGen); // not implemented
    RndNumGenerator& operator=(const RndNumGenerator & rndGen); // not implemented

    PRNG prng; // there can only be single instance of PRNG through RndNUmGenerator
};

#endif // __RNDNUMGENERATOR_H_
