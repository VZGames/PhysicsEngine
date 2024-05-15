#ifndef QUADTREE_H
#define QUADTREE_H

#include <stdlib.h>
#include <stdio.h>
#include "Math/Rect2D.h"
#include "DataStructs/DoublyLinkedList.h"
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
    List* objects; // list of objects
    QuadTree* nodes[QuadtreeNode::NodeLimit]; // list of nodes
};

int hash(QuadTree* node, float x, float y); // get cell index
QuadTree* CreateQuadTreeNode(float width, float height)
{
    QuadTree* node = (QuadTree*)malloc(sizeof(QuadTree));
    node->objects = CreateList();
    node->rect.A = (Vec2){0, 0};
    node->rect.C = (Vec2){width, height};
    Vec2 size = subtract(node->rect.C, node->rect.A);

    for (int i = QuadtreeNode::WestNorth; i < QuadtreeNode::NodeLimit; i++)
    {
        node->nodes[i] = (QuadTree*)malloc(sizeof(QuadTree));
    }

    node->nodes[WestNorth]->rect.A.x    =  node->rect.A.x;
    node->nodes[WestNorth]->rect.A.y    =  node->rect.A.y;
    node->nodes[WestNorth]->rect.C.x    =  node->rect.A.x + size.x/2;
    node->nodes[WestNorth]->rect.C.y    =  node->rect.A.y + size.y/2;

    node->nodes[EastNorth]->rect.A.x    =  node->rect.A.x + size.x/2;
    node->nodes[EastNorth]->rect.A.y    =  node->rect.A.y;
    node->nodes[EastNorth]->rect.C.x    =  node->rect.A.x + size.x;
    node->nodes[EastNorth]->rect.C.y    =  node->rect.A.y + size.y/2;

    node->nodes[EastSouth]->rect.A.x    =  node->rect.A.x;
    node->nodes[EastSouth]->rect.A.y    =  node->rect.A.y + size.y/2;
    node->nodes[EastSouth]->rect.C.x    =  node->rect.A.x + size.x/2;
    node->nodes[EastSouth]->rect.C.y    =  node->rect.A.y + size.y;

    node->nodes[WestSouth]->rect.A.x    =  node->rect.A.x + size.x/2;
    node->nodes[WestSouth]->rect.A.y    =  node->rect.A.y + size.y/2;
    node->nodes[WestSouth]->rect.C.x    =  node->rect.C.x;
    node->nodes[WestSouth]->rect.C.y    =  node->rect.C.y;
    return node;
}

void Insert(QuadTree* node, void* obj)
{
    if (node == NULL) return;
    if (obj == NULL) return;

    Body2D* body = (Body2D*)obj;
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

void Clear(QuadTree* node)
{
//    if (node != NULL)
//    {
//        // Clear all nodes
//        for (int i = QuadtreeNode::WestNorth; i < QuadtreeNode::NodeLimit; i++)
//        {
//            Clear(node->nodes[i]);
//            free(node->nodes[i]);
//            node->nodes[i] = 0;
//        }
//        free(node);
//        node = NULL;
//    }

    // Clear current Quadtree
//    for (int i = 0; i < (int)node->numOfObjects; i++)
//    {
//        if (node->objects[i] == NULL) continue;
//        free(node->objects[i]);
//    }

    Clear(node->objects);
}

bool IsContain(QuadTree* node, void* obj)
{

}


#endif // QUADTREE_H
