#include "UiApplication.hpp"

#include "common/Utils.hpp"

namespace kygon::client {

namespace {
// TODO: temp
QByteArray kUsername{"username1"};
const QUrl kMainQmlUrl(u"qrc:/kygon/qml/main.qml"_qs);
}  // namespace

UiApplication::UiApplication(int argc, char* argv[]) : QGuiApplication{argc, argv} {}

bool UiApplication::init() {
    QObject::connect(
        &m_qmlEngine, &QQmlApplicationEngine::objectCreationFailed, this,
        []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
    m_qmlEngine.load(kMainQmlUrl);

    return true;
}

}  // namespace kygon::client
