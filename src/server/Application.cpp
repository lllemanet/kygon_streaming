#include "Application.hpp"

#include "common/Utils.hpp"

namespace kygon::server {

namespace {
// TODO: get from argv
const QHostAddress kServerAddress{"127.0.0.1"};
const uint16_t kServerPort{29118};
}  // namespace

Application::Application(int argc, char* argv[]) : QCoreApplication{argc, argv} {}

bool Application::init() {
    if (!connect(&m_server, &QTcpServer::newConnection,
                 [this]() { m_clientsMediator.addClientSession(m_server.nextPendingConnection()); })) {
        qKDebug() << "Can't connect QTcpServer::newConnection to clients mediator";
        return false;
    }

    if (!m_server.listen(kServerAddress, kServerPort)) {
        qKDebug() << "Can't listen on " << kServerAddress << ":" << kServerPort;
        return false;
    }

    return true;
}

}  // namespace kygon::server
