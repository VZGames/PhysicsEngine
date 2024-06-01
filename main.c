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
    printf("%d\n", *(int*)data);
}

int main()
{
    World2D *world = CreateWorld(9.8f, 5.0f, 3.0f);
    Circle* circle = CreateCircle((Vec2) {0.0f, 0.0f}, 0.5f);
    Array1D* array = CreateArray1D();
    Array1D* objs  = CreateArray1D();
    struct QuadTree* tree = CreateQuadTreeNode(NULL, world->w, world->h, 0);

    for (int k = 0; k < 5; ++k) {
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
        printf("+++++++++++++++++++++++++\n");
    }

    Body2D* obj = (Body2D*)Array1DItemAtIndex(objs, 0);
    QuadTreeRetrieve(tree, array, &obj->shape.box);

    printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
    Array1DTraverse(array, printArr);

    QuadTreeClear(tree);
    DestroyWorld(world);


    return 0;
}
