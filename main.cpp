#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTimer>

#include "World2D.h"
#include "Body2D.h"
#include "DataStructs/QuadTree.h"

#define FPS 60

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    W2D* world = CreateWorld(9.8f, 5.0f, 3.0f);

    B2D bodyA;
    bodyA.type = STATIC_TYPE;
    bodyA.density = 1.0f;
    bodyA.mass = 1.0f;
    bodyA.restitution = 0.3f;
    bodyA.position = (Vec2) {2.7f, 1.3f};

    B2D bodyB;
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


    BID Aid = CreateBody(world, &bodyA);
    BID Bid = CreateBody(world, &bodyB);

    SID shapeA = CreateShape(world, Aid, CIRCLE, &circle);
    SID shapeB = CreateShape(world, Bid, POLYGON, &polygon);

    float circle_area = shape_area(CIRCLE, &circle);
    float polygon_area = shape_area(POLYGON, &polygon);

    qDebug("Body Id index: %d, world: %p", Aid.index, Aid.world);
    qDebug("Shape Id index: %d, world: %p, area: %f", shapeA.index, shapeA.world, circle_area);
    qDebug("Body Id index: %d, world: %p", Bid.index, Bid.world);
    qDebug("Shape Id index: %d, world: %p, area: %f", shapeB.index, shapeB.world, polygon_area);



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
    free(tree);


    return app.exec();
}
