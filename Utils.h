#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdlib.h>

int randInt(int max)
{
    srand(time(NULL));
    return rand() % (max + 1);
}
float rantReal(float max)
{
    return (float)rand()/(float)(RAND_MAX/max);
}

bool randBit()
{
    return (bool)(rand() % (1));
}

#endif // UTILS_H
