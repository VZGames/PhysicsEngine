#ifndef WORLD_H
#define WORLD_H

typedef struct world
{
    float gravity;
    float w;
    float h;
} World;

void update_world(float deltatime, unsigned int total_iterations);
void broad_phase();
void narrow_phase();

#endif // WORLD_H
