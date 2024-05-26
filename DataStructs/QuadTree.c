#include "QuadTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <Body2D.h>

void PrintObject(void* vobj)
{
    Body2D* obj = (Body2D*)vobj;
    printf("Object: %p [%f, %f, %f, %f]\n", vobj, obj->shape.box.x, obj->shape.box.y, obj->shape.box.width, obj->shape.box.height);
}
struct QuadTree *CreateQuadTreeNode(const struct QuadTree* parent, float width, float height,  int index)
{
    struct QuadTree* node = (struct QuadTree*)malloc(sizeof(struct QuadTree));
    node->objects = CreateArray1D();
    if (parent == NULL) // current node is root, have not parent (NULL)
    {
        node->rect.x = 0;
        node->rect.y = 0;
        node->rect.width = width;
        node->rect.height = height;
    }
    else
    {
        node->rect.x    =  parent->rect.x + (index % 2) * width;
        node->rect.y    =  parent->rect.y + (index / 2) * height;
        node->rect.width    =  parent->rect.x + (width) + (width) * (index % 2);
        node->rect.height    =  parent->rect.y + (height) + (height) * (index / 2);
    }
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
                node->nodes[i] = CreateQuadTreeNode(node, node->rect.width / 2.0f, node->rect.height / 2.0f, i);
            }
            QuadtreeInsert(node->nodes[i], obj, objBoundary);
        }
    }

    printf("Boundary [%f %f %f %f] include %llu objects\n", node->rect.x, node->rect.y, node->rect.width, node->rect.height, Array1DTotalSize(node->objects));
    Array1DTraverse(node->objects, PrintObject);
    printf("\n");
}

int QuadTreehash(struct QuadTree *node, float x, float y)
{
    int columns = 2;
    int rows = 2;
    int hashX = (int)((x - node->rect.x) / (node->rect.width / 2.0f));
    int hashY = (int)((y - node->rect.y) / (node->rect.height / 2.0f));
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
    return (boundary->x >= node->rect.x || boundary->x + boundary->width <= node->rect.width)
           || (boundary->y >= node->rect.y || boundary->y + boundary->height <= node->rect.height);
}
