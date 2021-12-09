#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include <time.h>

// used to generate random number from current seed and update seed
const unsigned long maxshort  = 65536L;
const unsigned long multiplier = 1194211693L;
const unsigned long adder = 12345L;

class RandomNumberGenerator
{
    private:
        unsigned long randSeed;
    public:
        RandomNumberGenerator(unsigned long s = 0);
        unsigned short Random(unsigned long n);
        double fRandom(void);
};
        
#endif
