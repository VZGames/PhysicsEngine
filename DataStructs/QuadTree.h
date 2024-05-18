#ifndef QUADTREE_H
#define QUADTREE_H

#include "Math/Rect2D.h"
#include "Array1D.h"

typedef enum
{
    WestNorth,// TOP-LEFT (1)
    EastNorth,// TOP-RIGHT (2)
    WestSouth,// BOTTOM-LEFT (3)
    EastSouth,// BOTTOM-RIGHT (4)
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
void QuadtreeInsert(struct QuadTree* node, void* obj, const Vec2* position, const Rect2D* objBoundary);
void QuadTreeClear(struct QuadTree* node);
bool QuadTreeInclude(struct QuadTree* node, const Rect2D* boundary);

#endif // QUADTREE_H
