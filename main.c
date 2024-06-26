#include <stdio.h>
#include "World2D.h"
#include "Body2D.h"
#include "DataStructs/QuadTree.h"
#include "Utils.h"

void printList(void *data)
{
    Body2D *body = (Body2D*)data;
    printf("idx: %d\n", body->index);
}

void printArr(void *data)
{
    // Body2D* obj = (Body2D*)data;
    // printf("Object: %p [%f, %f, %f, %f]\n", obj, obj->shape.box.x, obj->shape.box.y, obj->shape.box.width, obj->shape.box.height);
    struct QuadTree* node = (struct QuadTree*)data;
    printf("Node: %p\n", data);
    for (int i = 0; i < node->objects->size; ++i) {
        Body2D* obj = (Body2D*)Array1DItemAtIndex(node->objects, i);
        printf("Object: %p [%f, %f, %f, %f]\n", obj, obj->shape.box.x, obj->shape.box.y, obj->shape.box.width, obj->shape.box.height);
    }
}

int main()
{
    World2D *world = CreateWorld(9.8f, 5.0f, 3.0f);
    Circle* circle = CreateCircle((Vec2) {0.0f, 0.0f}, 0.5f);
    Array1D* array = CreateArray1D();
    Array1D* objs  = CreateArray1D();
    struct QuadTree* tree = CreateQuadTreeNode(NULL, world->w, world->h, 0);

    for (int k = 0; k < 10; ++k) {
        Body2D body;
        body.type = STATIC_TYPE;
        body.density = 1.0f;
        body.mass = 1.0f;
        body.restitution = 0.3f;
        body.position = (Vec2) {
            randReal(0.0f, 4.0f),
            randReal(0.0f, 2.0f)
        };


        Body2D *obj = CreateBody(world, &body);
        BodyCreateShape(obj, CIRCLE, circle);
        
        Array1DPush(objs, obj);
        QuadtreeInsert(tree, obj, &obj->shape.box);
    }


    QuadTreePrint(tree);
    Body2D* obj = (Body2D*)Array1DItemAtIndex(objs, 0);
    QuadTreeSearch(tree, array, &obj->shape.box);
    printf("%lu\n", Array1DTotalSize(array));
    Array1DTraverse(array, printArr);

    QuadTreeClear(tree);
    DestroyWorld(world);


    return 0;
}
