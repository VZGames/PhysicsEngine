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
    WestSouth,
    NodeLimit
} QuadtreeNode;

struct QuadTree
{
    Rect2D rect; // boundary
    void** objects; // list of objects
    QuadTree* nodes[QuadtreeNode::NodeLimit]; // list of nodes
};

int hash(QuadTree* node, float x, float y); // get cell index
QuadTree* CreateQuadTreeNode(float window_width, float window_height)
{
    QuadTree* root = (QuadTree*)malloc(sizeof(QuadTree));
    root->rect.A = (Vec2){0, 0};
    root->rect.C = (Vec2){window_width, window_height};
    Vec2 size = subtract(root->rect.C, root->rect.A);

    for (int i = QuadtreeNode::WestNorth; i < QuadtreeNode::NodeLimit; i++)
    {
        root->nodes[i] = (QuadTree*)malloc(sizeof(QuadTree));
    }

    root->nodes[WestNorth]->rect.A.x    =  root->rect.A.x;
    root->nodes[WestNorth]->rect.A.y    =  root->rect.A.y;
    root->nodes[WestNorth]->rect.C.x    =  root->rect.A.x + size.x/2;
    root->nodes[WestNorth]->rect.C.y    =  root->rect.A.y + size.y/2;

    root->nodes[EastNorth]->rect.A.x    =  root->rect.A.x + size.x/2;
    root->nodes[EastNorth]->rect.A.y    =  root->rect.A.y;
    root->nodes[EastNorth]->rect.C.x    =  root->rect.A.x + size.x;
    root->nodes[EastNorth]->rect.C.y    =  root->rect.A.y + size.y/2;

    root->nodes[EastSouth]->rect.A.x    =  root->rect.A.x;
    root->nodes[EastSouth]->rect.A.y    =  root->rect.A.y + size.y/2;
    root->nodes[EastSouth]->rect.C.x    =  root->rect.A.x + size.x/2;
    root->nodes[EastSouth]->rect.C.y    =  root->rect.A.y + size.y;

    root->nodes[WestSouth]->rect.A.x    =  root->rect.A.x + size.x/2;
    root->nodes[WestSouth]->rect.A.y    =  root->rect.A.y + size.y/2;
    root->nodes[WestSouth]->rect.C.x    =  root->rect.C.x;
    root->nodes[WestSouth]->rect.C.y    =  root->rect.C.y;
    return root;
}

void Insert(QuadTree* node, void* obj)
{
    if (obj == NULL) return;
    if (node == NULL) return;
    B2D* body = (B2D*)obj;
    int index = hash(node, body->position.x, body->position.y);
    Insert(node->nodes[(QuadtreeNode)index], NULL); // have not anchor yet

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
