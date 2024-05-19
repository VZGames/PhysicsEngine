#include <stdio.h>
#include "World2D.h"
#include "Body2D.h"
#include "DataStructs/QuadTree.h"

void printList(void* data)
{
    Body2D* body = (Body2D*)data;
    printf("idx: %d\n", body->index);
}

void printArr(void* data)
{
    printf("%d\n", *(int*)data);
}

int main()
{
    World2D* world = CreateWorld(9.8f, 5, 3);

    Body2D bodyA;
    bodyA.type = STATIC_TYPE;
    bodyA.density = 1.0f;
    bodyA.mass = 1.0f;
    bodyA.restitution = 0.3f;
    bodyA.position = (Vec2) {2.7f, 1.3f};

    Body2D bodyB;
    bodyB.type = STATIC_TYPE;
    bodyB.density = 1.0f;
    bodyB.mass = 1.0f;
    bodyB.restitution = 0.3f;
    bodyB.position = (Vec2) {2.4f, 1.6f};

    Circle* circle = CreateCircle((Vec2) {0.0f, 0.0f}, 0.5f);

    Vec2 verties[6] = {
        (Vec2) { 0.0f, 0.0f},
        (Vec2) { 0.5f, -0.5f},
        (Vec2) { 1.0f, 0.0f},
        (Vec2) { 1.0f, 1.0f},
        (Vec2) { 0.5f, 1.5f},
        (Vec2) { 0.0f, 1.0f}
    };
    Polygon* polygon = CreatePolygon(&verties[0], sizeof(verties)/sizeof(Vec2));



    Body2D* objA = CreateBody(world, &bodyA);
    Body2D* objB = CreateBody(world, &bodyB);

    Shape2D shapeA = CreateShapeForBody(objA, CIRCLE, circle);
    Shape2D shapeB = CreateShapeForBody(objB, POLYGON, polygon);

    float circle_area = GetShapeArea(shapeA);
    float polygon_area = GetShapeArea(shapeB);

    (void)circle_area;
    (void)polygon_area;

    struct QuadTree* tree = CreateQuadTreeNode("Root", world->w, world->h);
    QuadtreeInsert(tree, objA, &objA->position, &objA->shape.boundary);
    QuadtreeInsert(tree, objB, &objB->position, &objB->shape.boundary);

    QuadTreeClear(tree);
    DestroyWorld(world);


    return 0;
}
