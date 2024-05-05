#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "World2D.h"
#include "Body2D.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    W2D* world = CreateWorld(9.8f, 5.0f, 3.0f);
    B2D* body = CreateBody(world);
    DestroyBody(body);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);


    return app.exec();
}
