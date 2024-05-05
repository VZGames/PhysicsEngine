#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlApplicationEngine>

#include "World2D.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);


    return app.exec();
}
