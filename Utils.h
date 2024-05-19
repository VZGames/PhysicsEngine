#ifndef UTILS__H
#define UTILS__H

#include <stdlib.h>
#include <stdbool.h>

inline int randInt(int max)
{
    return rand() % (max + 1);
}

inline float randReal(float max)
{
    return (float)rand()/(float)(RAND_MAX/max);
}

inline bool randBit()
{
    return (bool)(rand() % (1));
}

#endif // UTILS__H
