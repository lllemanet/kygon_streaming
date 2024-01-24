#include "ClientsMediator.hpp"

#include "ClientSession.hpp"
#include "common/Utils.hpp"

namespace kygon::server {

ClientsMediator::ClientsMediator(QObject* parent) : QObject{parent} {}

void ClientsMediator::addClientSession(QTcpSocket* socket) {
    ClientSession* session = new ClientSession{*socket};
    m_clientSessions.push_back(session);
    connect(session, &ClientSession::closed, [this, session] {
        qKDebug() << "ServerSession closed: " << session->toString();
        m_clientSessions.removeOne(session);
        session->deleteLater();
    });
}

}  // namespace kygon::server
