#ifndef WORLD2D_H
#define WORLD2D_H

#define MAX_BODY 255
#define MAX_SHAPE 1024

typedef struct world_2d_define
{
    float gravity;
    float w;
    float h;
    bool* body_bitset;
    bool* shape_bitset;
    void* bodies[MAX_BODY];
    void* shapes[MAX_SHAPE];
} W2D;

W2D *CreateWorld(float g, float w, float h);
void DestroyWorld(W2D* world);

void Update(W2D* world, float deltatime, int totalIterations);
void BroadPhase();
void NarrowPhase();

#endif // WORLD2D_H
