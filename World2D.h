#ifndef WORLD2D_H
#define WORLD2D_H

#define MIN_BODY_SIZE (0.25f);
#define MAX_BODY_SIZE (3.0f);

#define MAX_BODY 255
#define MAX_SHAPE 1024

typedef struct world_2d_define
{
    float gravity;
    unsigned char w;
    unsigned char h;
    bool* bodyBitset;
    bool* shapeBitset;
    void* bodies[MAX_BODY];
    void* shapes[MAX_SHAPE];
} W2D;

W2D *CreateWorld(float g, unsigned char w, unsigned char h);
void DestroyWorld(W2D* world);

void Update(W2D* world, float deltatime, int totalIterations);
void BroadPhase(W2D* world);
void NarrowPhase(W2D* world);

#endif // WORLD2D_H
