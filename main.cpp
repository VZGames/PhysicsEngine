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

    B2D body;
    body.type = STATIC_TYPE;
    body.density = 1.0f;
    body.mass = 1.0f;
    body.restitution = 0.3f;
    body.position = (Vec2) {30, 50};

    Circle circle;
    circle.center = (Vec2) {0.0f, 0.0f};
    circle.radius = 1.0f;

    BID id = CreateBody(world, &body);
    SID shapeA = CreateShape(world, id, CIRCLE, &circle);
    SID shapeB = CreateShape(world, id, CIRCLE, &circle);

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
