#include "RndNumGenerator.h"
#include <iostream>
using namespace std;

/*
 * NOTE: please refer to RndNumGenerator.h for method specific comments
 */

RndNumGenerator::RndNumGenerator()
: prng()
{}

RndNumGenerator& RndNumGenerator::getInstance()
{
    // not thread-safe but it's okay since it gets called before a new thread is created
    static RndNumGenerator rndGen;
    return rndGen;
}

void RndNumGenerator::seed( uint32_t s )
{
    prng.seed(s);
}

uint32_t RndNumGenerator::operator()()
{
    return prng();
}

uint32_t RndNumGenerator::operator()( uint32_t u )
{
    return prng(u);
}

uint32_t RndNumGenerator::operator()( uint32_t l, uint32_t u )
{
    return prng(l, u);
}
