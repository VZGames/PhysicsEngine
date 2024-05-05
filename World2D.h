#ifndef WORLD2D_H
#define WORLD2D_H

#define MAX_BODY 255

typedef struct world_2d_define
{
    float gravity;
    float w;
    float h;
    void* bodies[MAX_BODY];
} WorldDef;


#endif // WORLD2D_H
