#ifndef UTILS__H
#define UTILS__H

#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

inline int randInt(int max)
{
    srand((unsigned int)time(NULL));
    return rand() % (max + 1);
}

inline float rantReal(float max)
{
    return (float)rand()/(float)(RAND_MAX/max);
}

inline bool randBit()
{
    return (bool)(rand() % (1));
}

#endif // UTILS__H
