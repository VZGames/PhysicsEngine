#include "QuadTree.h"
#include <stdlib.h>
#include <stdio.h>

struct QuadTree *CreateQuadTreeNode(char* name, float width, float height)
{
    struct QuadTree* node = (struct QuadTree*)malloc(sizeof(struct QuadTree));
    node->name = name;
    node->objects = CreateArray1D();
    node->rect.A = (Vec2){0, 0};
    node->rect.C = (Vec2){width, height};
    node->nodes[WestNorth] = NULL; // TOP-LEFT (1)
    node->nodes[EastNorth] = NULL; // TOP-RIGHT (2)
    node->nodes[WestSouth] = NULL; // BOTTOM-LEFT (3)
    node->nodes[EastSouth] = NULL; // BOTTOM-RIGHT (4)

    return node;
}

void QuadtreeInsert(struct QuadTree *node, void *obj, const Vec2* position, const Rect2D* objBoundary)
{
    if (node == NULL || obj == NULL || position == NULL) return;

    if (QuadTreeAbsInclude(node, objBoundary))
    {
        printf("Node: %p contain object %p\n", node, obj);
        Array1DPush(node->objects, obj);
    }

//    Vec2 size = subtract(node->rect.C, node->rect.A);
//    if (Array1DTotalSize(node->objects) > 2)
//    {
//        int index = QuadTreehash(node, position->x, position->y);

//        char name[1024];
//        sprintf_s(&name[0], sizeof(name)/sizeof(char), "%s [%p] -> %d", node->name, node, index);
//        printf("%s %p\n", node->name, obj);

//        node->nodes[index] = CreateQuadTreeNode(name, size.x/2, size.y/2);
//        node->nodes[index]->rect.A.x    =  node->rect.A.x + (index % 2) * size.x/2;
//        node->nodes[index]->rect.A.y    =  node->rect.A.y + (index / 2) * size.y/2;
//        node->nodes[index]->rect.C.x    =  node->rect.A.x + (size.x/2) + (size.x/2) * (index % 2);
//        node->nodes[index]->rect.C.y    =  node->rect.A.y + (size.y/2) + (size.y/2) * (index / 2);
//        QuadtreeInsert(node->nodes[index], obj, position, objBoundary); // have not anchor yet
//        //        if (QuadTreeAbsInclude(node->nodes[index], objBoundary))
//        //        {
//        //            printf("Node: %p contain object %p\n", node, obj);
//        //            //            Array1DPush(node->nodes[index]->objects, obj);
//        //        }
//    }

}

int QuadTreehash(struct QuadTree *node, float x, float y)
{
    Vec2 size = Vec2Subtract(node->rect.C, node->rect.A);
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
    if (node != NULL)
    {
        // Clear all nodes
        for (int i = WestNorth; i < NodeLimit; i++)
        {
            QuadTreeClear(node->nodes[i]);
        }
        Array1DClear(node->objects);
        free(node);
        node = NULL;
    }
}

bool QuadTreeAbsInclude(struct QuadTree *node, const Rect2D* boundary)
{
    return !(boundary->C.x < node->rect.A.x ||
             boundary->C.y < node->rect.A.y ||
             boundary->A.x > node->rect.C.x ||
             boundary->A.y > node->rect.C.y);
}
