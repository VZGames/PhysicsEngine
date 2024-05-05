#include "World.h"

void update_world(float deltatime, unsigned int total_iterations)
{
    (void)deltatime;
    for (unsigned int it = 0; it < total_iterations; it++) {
        broad_phase();
        narrow_phase();
    }
}

void broad_phase()
{

}

void narrow_phase()
{

}
