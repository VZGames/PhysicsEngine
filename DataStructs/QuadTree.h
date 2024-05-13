#ifndef QUADTREE_H
#define QUADTREE_H

#include <stdio.h>
#include "Math/Rect2D.h"
#include "Body2D.h"

typedef enum quad_tree_node: int
{
    WestNorth,
    EastNorth,
    EastSouth,
    WestSouth
} QuadtreeNode;

struct QuadTree
{
    Rect2D rect; // boundary
    void** objects; // list of objects
    QuadTree* nodes[4]; // list of nodes
};

int hash(QuadTree* node, float x, float y); // get cell index
QuadTree* CreateQuadTreeNode(float window_width, float window_height)
{
    QuadTree* root = (QuadTree*)malloc(sizeof(QuadTree));
    root->rect.A = (Vec2){0, 0};
    root->rect.C = (Vec2){window_width, window_height};
    root->nodes[WestNorth] = NULL;
    root->nodes[EastNorth] = NULL;
    root->nodes[EastSouth] = NULL;
    root->nodes[WestSouth] = NULL;
    return root;
}

void Insert(QuadTree* node, void* obj)
{
    B2D* body = (B2D*)obj;
    int index = hash(node, body->position.x, body->position.y);
}

int hash(QuadTree* node, float x, float y) // get cell index
{
    Vec2 size = subtract(node->rect.C, node->rect.A);
    int columns = 2;
    int rows = 2;
    int hashX = ((x - node->rect.A.x) / (size.x / 2.0f));
    int hashY = ((y - node->rect.A.y) / (size.y / 2.0f));
    if(hashX < 0) hashX = 0;
    if(hashX > columns) hashX = columns - 1;
    if(hashY < 0) hashY = 0;
    if(hashY > rows) hashY = rows - 1;

    return ((hashY * columns) + hashX);
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
