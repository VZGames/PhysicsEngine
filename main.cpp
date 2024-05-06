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
    BodyID body = CreateBody(world);
    DestroyBody(body);

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
