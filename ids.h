#ifndef IDS_H
#define IDS_H

typedef struct body_id
{
    int index;
    void* world;
} BodyID;

typedef struct shape_id
{
    int index;
    int body;
} ShapeID;

#endif // IDS_H
