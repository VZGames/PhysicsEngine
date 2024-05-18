#include "QuadTree.h"
#include <stdlib.h>
#include <stdio.h>
#include "World2D.h"

struct QuadTree *CreateQuadTreeNode(float width, float height)
{
    struct QuadTree* node = (struct QuadTree*)malloc(sizeof(struct QuadTree));
    node->objects = CreateArray1D();
    node->rect.A = (Vec2){0, 0};
    node->rect.C = (Vec2){width, height};
    node->nodes[WestNorth] = NULL; // TOP-LEFT (1)
    node->nodes[EastNorth] = NULL; // TOP-RIGHT (2)
    node->nodes[WestSouth] = NULL; // BOTTOM-LEFT (3)
    node->nodes[EastSouth] = NULL; // BOTTOM-RIGHT (4)
    return node;
}

void QuadtreeInsert(struct QuadTree *node, void *obj, Vec2* position)
{
    if (node == NULL || obj == NULL || position == NULL) return;
    Vec2 size = subtract(node->rect.C, node->rect.A);

    if ((size.x * size.y) > MIN_BODY_SIZE)
    {
        QuadtreeNode index = (QuadtreeNode)QuadTreehash(node, position->x, position->y);
        node->nodes[index] = CreateQuadTreeNode(size.x/2, size.y/2);
        switch (index) {
        case WestNorth:
        {
            node->nodes[WestNorth]->rect.A.x    =  node->rect.A.x;
            node->nodes[WestNorth]->rect.A.y    =  node->rect.A.y;
            node->nodes[WestNorth]->rect.C.x    =  node->rect.A.x + size.x/2;
            node->nodes[WestNorth]->rect.C.y    =  node->rect.A.y + size.y/2;
            break;
        }
        case EastNorth:
        {
            node->nodes[EastNorth]->rect.A.x    =  node->rect.A.x + size.x/2;
            node->nodes[EastNorth]->rect.A.y    =  node->rect.A.y;
            node->nodes[EastNorth]->rect.C.x    =  node->rect.A.x + size.x;
            node->nodes[EastNorth]->rect.C.y    =  node->rect.A.y + size.y/2;
            break;
        }
        case WestSouth:
        {
            node->nodes[WestSouth]->rect.A.x    =  node->rect.A.x;
            node->nodes[WestSouth]->rect.A.y    =  node->rect.A.y + size.y/2;
            node->nodes[WestSouth]->rect.C.x    =  node->rect.A.x + size.x/2;
            node->nodes[WestSouth]->rect.C.y    =  node->rect.A.y + size.y;
            break;
        }
        case EastSouth:
        {
            node->nodes[EastSouth]->rect.A.x    =  node->rect.A.x + size.x/2;
            node->nodes[EastSouth]->rect.A.y    =  node->rect.A.y + size.y/2;
            node->nodes[EastSouth]->rect.C.x    =  node->rect.C.x;
            node->nodes[EastSouth]->rect.C.y    =  node->rect.C.y;
            break;
        }
        default:
            break;
        }

        QuadtreeInsert(node->nodes[index], obj, position); // have not anchor yet
    }
}

int QuadTreehash(struct QuadTree *node, float x, float y)
{
    Vec2 size = subtract(node->rect.C, node->rect.A);
    int columns = 2;
    int rows = 2;
    int hashX = (int)((x - node->rect.A.x) / (size.x / 2.0f));
    int hashY = (int)((y - node->rect.A.y) / (size.y / 2.0f));
    if(hashX < 0) hashX = 0;
    if(hashX > columns) hashX = columns - 1;
    if(hashY < 0) hashY = 0;
    if(hashY > rows) hashY = rows - 1;
    return ((hashY * columns) + hashX);
}

void QuadTreeClear(struct QuadTree *node)
{
    //    if (node != NULL)
    //    {
    //        // Clear all nodes
    //        for (int i = WestNorth; i < NodeLimit; i++)
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

    Array1DClear(node->objects);
}

bool QuadTreeInclude(struct QuadTree *node, void *obj)
{
    return true;
}
