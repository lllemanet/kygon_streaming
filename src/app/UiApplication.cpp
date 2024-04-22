#include "UiApplication.hpp"

#include "common/Utils.hpp"

namespace kygon::client {

namespace {
// TODO: temp
QByteArray kUsername{"username1"};
const QUrl kMainQmlUrl(u"qrc:/kygon/main.qml"_qs);
}  // namespace

UiApplication::UiApplication(int argc, char* argv[]) : QGuiApplication{argc, argv} {}

bool UiApplication::init() {
    if (arguments().size() < 3) {
        qKDebug() << "Invalid arguments\n"
                  << "Usage: " << arguments().at(0) << " <server-address> <server-port>";
        return false;
    }

    // Init ChatManager
    QHostAddress address{arguments().at(1)};
    auto port = arguments().at(2).toUInt();
    if (!m_chatManager.init(address, port, kUsername)) {
        qKDebug() << "Can't init server session for " << address.toString() << ":" << port;
        return false;
    }

    // TODO: recover?
    connect(&m_chatManager, &ChatManager::closed, []() {
        qKCritical() << "ChatManager closed, exitting app";
        QCoreApplication::exit(-1);
    });

    // Init QML UI
    QObject::connect(
        &m_qmlEngine, &QQmlApplicationEngine::objectCreationFailed, this,
        []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
    m_qmlEngine.load(kMainQmlUrl);

    return true;
}

}  // namespace kygon::client
