#ifndef QUADTREE_H
#define QUADTREE_H

#include "Math/Rect2D.h"

struct QuadTree
{
    Rect2D rect; // boundary
    void** objects; // list of objects
    QuadTree** nodes; // list of nodes
};

QuadTree* CreateQuadTree()
{

}

void Insert(QuadTree* node, void* obj)
{

}

void Clear(QuadTree* tree)
{
    if (tree == NULL) return;
    else
    {

    }
}

bool IsContain(QuadTree* node, void* obj)
{

}


#endif // QUADTREE_H
