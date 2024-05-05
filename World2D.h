#ifndef WORLD2D_H
#define WORLD2D_H

#define MAX_BODY 255

typedef struct world_2d_define
{
    float gravity;
    float w;
    float h;
    bool* bits;
    void* bodies[MAX_BODY];
    void(*OnBodyDestruction)(void*);

} W2D;

W2D *CreateWorld(float g, float w, float h);
void DestroyWorld(W2D* world);

void Update(W2D* world, float deltatime, int totalIterations);
void BroadPhase();
void NarrowPhase();

void BodyDestroyedCallback(void* data);

#endif // WORLD2D_H
