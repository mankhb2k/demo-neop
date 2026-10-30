#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "playback.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Playback playback;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("playback", &playback);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("EditorCore", "Main");

    return QGuiApplication::exec();
}
