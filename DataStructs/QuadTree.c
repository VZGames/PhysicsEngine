#include "QuadTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <Body2D.h>

void PrintObject(void* vobj)
{
    Body2D* obj = (Body2D*)vobj;
    printf("Object: %p [%f, %f, %f, %f]\n", vobj, obj->shape.boundary.A.x, obj->shape.boundary.A.y, obj->shape.boundary.C.x, obj->shape.boundary.C.y);
}
struct QuadTree *CreateQuadTreeNode(const struct QuadTree* parent, float width, float height,  int index)
{
    struct QuadTree* node = (struct QuadTree*)malloc(sizeof(struct QuadTree));
    node->objects = CreateArray1D();
    if (parent == NULL) // current node is root, have not parent (NULL)
    {
        node->rect.A = (Vec2) {0,0};
        node->rect.C = (Vec2) {width, height};
    }
    else
    {
        node->rect.A.x    =  parent->rect.A.x + (index % 2) * width;
        node->rect.A.y    =  parent->rect.A.y + (index / 2) * height;
        node->rect.C.x    =  parent->rect.A.x + (width) + (width) * (index % 2);
        node->rect.C.y    =  parent->rect.A.y + (height) + (height) * (index / 2);
    }
    node->sizeOfRect  =  Vec2Subtract(node->rect.C, node->rect.A);
    node->nodes[WestNorth] = NULL; // TOP-LEFT (1)
    node->nodes[EastNorth] = NULL; // TOP-RIGHT (2)
    node->nodes[WestSouth] = NULL; // BOTTOM-LEFT (3)
    node->nodes[EastSouth] = NULL; // BOTTOM-RIGHT (4)

    return node;
}

void QuadtreeInsert(struct QuadTree *node, void *obj, const Rect2D* objBoundary)
{
    if (node == NULL) return;
    if (QuadTreeAbsInclude(node, objBoundary))
    {
        Array1DPush(node->objects, obj);
    }

    if (Array1DTotalSize(node->objects) > 1)
    {
        for (int i = WestNorth; i < NodeLimit; ++i) {
            if (node->nodes[i] == NULL)
            {
                node->nodes[i] = CreateQuadTreeNode(node, node->sizeOfRect.x/2.0f, node->sizeOfRect.y/2.0f, i);
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
    return (boundary->A.x >= node->rect.A.x && boundary->C.x <= node->rect.C.x)
           || (boundary->A.y >= node->rect.A.y && boundary->C.y <= node->rect.C.y);
}
