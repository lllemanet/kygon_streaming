#include "Application.hpp"

#include "common/Utils.hpp"

namespace kygon::server {

Application::Application(int argc, char* argv[]) : QCoreApplication{argc, argv} {}

bool Application::init() {
    if (arguments().size() < 3) {
        qKDebug() << "Invalid arguments\n"
                  << "Usage: " << arguments().at(0) << " <server-address> <server-port>";
        return false;
    }

    if (!connect(&m_server, &QTcpServer::newConnection,
                 [this]() { m_clientsMediator.addClientSession(m_server.nextPendingConnection()); })) {
        qKDebug() << "Can't connect QTcpServer::newConnection to clients mediator";
        return false;
    }

    QHostAddress address{arguments().at(1)};
    auto port = arguments().at(2).toUInt();
    if (!m_server.listen(address, port)) {
        qKDebug() << "Can't listen on " << address.toString() << ":" << port;
        return false;
    }

    return true;
}

}  // namespace kygon::server
