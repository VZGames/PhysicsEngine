#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTimer>

#include "World2D.h"
#include "Body2D.h"
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
    bodyA.position = (Vec2) {30, 50};

    B2D bodyB;
    bodyB.type = STATIC_TYPE;
    bodyB.density = 1.0f;
    bodyB.mass = 1.0f;
    bodyB.restitution = 0.3f;
    bodyB.position = (Vec2) {30, 50};

    Circle circle;
    circle.center = (Vec2) {0.0f, 0.0f};
    circle.radius = 1.0f;

    BID Aid = CreateBody(world, &bodyA);
    BID Bid = CreateBody(world, &bodyB);
    SID shapeA = CreateShape(world, Aid, CIRCLE, &circle);
    SID shapeB = CreateShape(world, Bid, CIRCLE, &circle);

    qDebug("Shape Id index: %d, body: %p", shapeA.index, shapeA.world);
    qDebug("Shape Id index: %d, body: %p", shapeB.index, shapeB.world);

    QTimer timer;
    timer.setInterval(FPS/1000);
    timer.callOnTimeout([&](){
        Update(world, FPS/1000, 10);
    });

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    timer.start();


    return app.exec();
}
