#include "QuadTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <Body2D.h>

void PrintObject(void* vobj)
{
    Body2D* obj = (Body2D*)vobj;
    printf("Object: %p [%f, %f, %f, %f]\n", vobj, obj->shape.boundary.A.x, obj->shape.boundary.A.y, obj->shape.boundary.C.x, obj->shape.boundary.C.y);
}
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

void QuadtreeInsert(struct QuadTree *node, void *obj, const Rect2D* objBoundary)
{
    Vec2 size = Vec2Subtract(node->rect.C, node->rect.A);
//    if (node != NULL)
//    {
//        for (int i = WestNorth; i < NodeLimit; ++i) {
//            if (node->nodes[i] == NULL)
//            {
//                node->nodes[i] = CreateQuadTreeNode(size.x/2, size.y/2);
//                node->nodes[i]->rect.A.x    =  node->rect.A.x + (i % 2) * size.x/2;
//                node->nodes[i]->rect.A.y    =  node->rect.A.y + (i / 2) * size.y/2;
//                node->nodes[i]->rect.C.x    =  node->rect.A.x + (size.x/2) + (size.x/2) * (i % 2);
//                node->nodes[i]->rect.C.y    =  node->rect.A.y + (size.y/2) + (size.y/2) * (i / 2);
//            }

//            if (QuadTreeAbsInclude(node->nodes[i], objBoundary))
//            {
//                QuadtreeInsert(node->nodes[i], obj, objBoundary);
//            }
//        }
//        return;
//    }

    if (node == NULL) return;
    if (QuadTreeAbsInclude(node, objBoundary))
    {
        Array1DPush(node->objects, obj);
    }

    if (Array1DTotalSize(node->objects) > 2)
    {
        for (int i = WestNorth; i < NodeLimit; ++i) {
            if (node->nodes[i] == NULL)
            {
                node->nodes[i] = CreateQuadTreeNode(size.x/2, size.y/2);
                node->nodes[i]->rect.A.x    =  node->rect.A.x + (i % 2) * size.x/2;
                node->nodes[i]->rect.A.y    =  node->rect.A.y + (i / 2) * size.y/2;
                node->nodes[i]->rect.C.x    =  node->rect.A.x + (size.x/2) + (size.x/2) * (i % 2);
                node->nodes[i]->rect.C.y    =  node->rect.A.y + (size.y/2) + (size.y/2) * (i / 2);
            }
            QuadtreeInsert(node->nodes[i], obj, objBoundary);
        }
    }
    printf("Boundary [%f %f %f %f] include %llu objects\n", node->rect.A.x, node->rect.A.y, node->rect.C.x, node->rect.C.y, Array1DTotalSize(node->objects));
    Array1DTraverse(node->objects, PrintObject);
    printf("\n");
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
    return !(boundary->A.x > node->rect.C.x ||
             boundary->A.y > node->rect.C.y ||
             boundary->C.x < node->rect.A.x ||
             boundary->C.y < node->rect.A.y);
}
