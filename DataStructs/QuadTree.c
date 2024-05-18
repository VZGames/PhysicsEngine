#include "QuadTree.h"

struct QuadTree *CreateQuadTreeNode(float width, float height)
{
    struct QuadTree* node = (struct QuadTree*)malloc(sizeof(struct QuadTree));
    node->objects = CreateArray1D();
    node->rect.A = (Vec2){0, 0};
    node->rect.C = (Vec2){width, height};
    Vec2 size = subtract(node->rect.C, node->rect.A);

    for (int i = WestNorth; i < NodeLimit; i++)
    {
        node->nodes[i] = (struct QuadTree*)malloc(sizeof(struct QuadTree));
    }

    if (node->nodes[WestNorth] != NULL)
    {
        node->nodes[WestNorth]->rect.A.x    =  node->rect.A.x;
        node->nodes[WestNorth]->rect.A.y    =  node->rect.A.y;
        node->nodes[WestNorth]->rect.C.x    =  node->rect.A.x + size.x/2;
        node->nodes[WestNorth]->rect.C.y    =  node->rect.A.y + size.y/2;
    }
    if (node->nodes[EastNorth] != NULL)
    {
        node->nodes[EastNorth]->rect.A.x    =  node->rect.A.x + size.x/2;
        node->nodes[EastNorth]->rect.A.y    =  node->rect.A.y;
        node->nodes[EastNorth]->rect.C.x    =  node->rect.A.x + size.x;
        node->nodes[EastNorth]->rect.C.y    =  node->rect.A.y + size.y/2;
    }
    if (node->nodes[EastSouth] != NULL)
    {
        node->nodes[EastSouth]->rect.A.x    =  node->rect.A.x;
        node->nodes[EastSouth]->rect.A.y    =  node->rect.A.y + size.y/2;
        node->nodes[EastSouth]->rect.C.x    =  node->rect.A.x + size.x/2;
        node->nodes[EastSouth]->rect.C.y    =  node->rect.A.y + size.y;
    }
    if (node->nodes[WestSouth] != NULL)
    {
        node->nodes[WestSouth]->rect.A.x    =  node->rect.A.x + size.x/2;
        node->nodes[WestSouth]->rect.A.y    =  node->rect.A.y + size.y/2;
        node->nodes[WestSouth]->rect.C.x    =  node->rect.C.x;
        node->nodes[WestSouth]->rect.C.y    =  node->rect.C.y;
    }
    return node;
}

void QuadtreeInsert(struct QuadTree *node, void *obj, Vec2* position)
{
    if (node == NULL) return;
    if (obj == NULL) return;
    int index = QuadTreehash(node, position->x, position->y);
    QuadtreeInsert(node->nodes[(QuadtreeNode)index], NULL, position); // have not anchor yet
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

bool IsContain(struct QuadTree *node, void *obj)
{
    return true;
}
