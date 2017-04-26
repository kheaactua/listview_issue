#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "blobs.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Blobs>("matt", 1, 0, "Blobs");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
