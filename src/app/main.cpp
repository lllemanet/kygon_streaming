#include <QQmlApplicationEngine>

#include "UiApplication.hpp"
#include "common/Utils.hpp"

int main(int argc, char *argv[]) {
    kygon::client::UiApplication app(argc, argv);
    if (!app.init()) {
        qKCritical() << "Can't init UiApplication";
        return -1;
    }

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/kygon/Main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
