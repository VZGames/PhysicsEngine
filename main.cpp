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

    Circle circle;
    circle.center = (Vec2) {0.0f, 0.0f};
    circle.radius = 3.0f;


    Polygon polygon;
    polygon.count = 6;
    polygon.points = (Vec2*)malloc(polygon.count * sizeof(Vec2));
    polygon.points[0] = (Vec2) { 0.0f, 0.0f};
    polygon.points[1] = (Vec2) { 0.5f, -0.5f};
    polygon.points[2] = (Vec2) { 1.0f, 0.0f};
    polygon.points[3] = (Vec2) { 1.0f, 1.0f};
    polygon.points[4] = (Vec2) { 0.5f, 1.5f};
    polygon.points[5] = (Vec2) { 0.0f, 1.0f};


    Body2D* objA = CreateBody(world, &bodyA);
    Body2D* objB = CreateBody(world, &bodyB);

    Shape2D* shapeA = CreateShape(objA, CIRCLE, &circle);
    Shape2D* shapeB = CreateShape(objB, POLYGON, &polygon);

    float circle_area = shape_area(CIRCLE, &circle);
    float polygon_area = shape_area(POLYGON, &polygon);

    qDebug("Body Id index: %d", objA->index);
    qDebug("Shape Id address: %p, area: %f", shapeA, circle_area);
    qDebug("Body Id index: %d", objB->index);
    qDebug("Shape Id address: %p, area: %f", shapeB, polygon_area);



    QuadTree* tree = CreateQuadTreeNode(world->w, world->h);
    Insert(tree, &bodyA);
    Insert(tree, &bodyB);

    QTimer timer;
    timer.setInterval(FPS/1000);
    timer.callOnTimeout([&](){
        Update(world, FPS/1000, 10);
    });

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    timer.start();
    Clear(tree);

    return app.exec();
}
