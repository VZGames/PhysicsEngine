#ifndef QUADTREE_H
#define QUADTREE_H

#include "Math/Rect2D.h"
#include "Array1D.h"

typedef enum
{
    WestNorth,
    EastNorth,
    EastSouth,
    WestSouth,
    NodeLimit
} QuadtreeNode;

struct QuadTree
{
    Rect2D rect; // boundary
    Array1D* objects; // list of objects
    struct QuadTree* nodes[NodeLimit]; // list of nodes
};

struct QuadTree* CreateQuadTreeNode(float width, float height);
int QuadTreehash(struct QuadTree* node, float x, float y); // get cell index
void QuadtreeInsert(struct QuadTree* node, void* obj, Vec2* position);
void QuadTreeClear(struct QuadTree* node);
bool QuadTreeInclude(struct QuadTree* node, void* obj);

#endif // QUADTREE_H
