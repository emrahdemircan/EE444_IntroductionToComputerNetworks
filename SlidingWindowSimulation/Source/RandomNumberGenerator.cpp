//
//  RandomNumberGenerator.cpp
//  SlidingWindowSimulation
//
//  Created by Demircan on 7.12.2021.
//

#include <stdio.h>
#include "RandomNumberGenerator.h"

RandomNumberGenerator::RandomNumberGenerator(unsigned long s)
{
    if(s == 0)
    {
        randSeed = time(0);
    }
    else
    {
        randSeed = s;
    }
}

unsigned short RandomNumberGenerator::Random(unsigned long n)
{
    randSeed = multiplier * randSeed + adder;
    return (unsigned short)((randSeed >> 16)  % n);
}

double RandomNumberGenerator::fRandom(void)
{
    return Random(maxshort)/double(maxshort);
}
