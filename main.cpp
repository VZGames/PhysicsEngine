#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTimer>

#include "World2D.h"
#include "Body2D.h"
#include "DataStructs/QuadTree.h"
#include "DataStructs/DoublyLinkedList.h"
#define FPS 60

void print(void* data)
{
    Body2D* body = (Body2D*)data;
    printf("idx: %d\n", body->index);
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    World2D* world = CreateWorld(9.8f, 5.0f, 3.0f);

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

    Circle* circle = CreateCircle((Vec2) {0.0f, 0.0f}, 3.0f);

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

    qDebug("Body Id index: %d", objA->index);
    qDebug("Shape Id address: %p, area: %f", &shapeA, circle_area);
    qDebug("Body Id index: %d", objB->index);
    qDebug("Shape Id address: %p, area: %f", &shapeB, polygon_area);

    List* list = CreateList();
    PushBack(list, objA);
    PushBack(list, objB);

    Body2D* data = (Body2D*)ElementAt(list, 2);
    printf("XXXXXXXXXX %d\n", data->index);
    Travel(list, print);

    //    QuadTree* tree = CreateQuadTreeNode(world->w, world->h);
    //    Insert(tree, &bodyA);
    //    Insert(tree, &bodyB);

    QTimer timer;
    timer.setInterval(FPS/1000);
    timer.callOnTimeout([&](){
        Update(world, FPS/1000, 10);
    });

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    timer.start();
    Clear(list);

    return app.exec();
}
