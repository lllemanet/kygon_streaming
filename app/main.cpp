#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine(u"qrc:/kygon/Main.qml"_qs);
    return app.exec();
}
