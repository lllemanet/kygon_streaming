#include "ClientsMediator.hpp"

#include "Session.hpp"
#include "common/Utils.hpp"

namespace kygon::server {

ClientsMediator::ClientsMediator(QObject* parent) : QObject{parent} {}

void ClientsMediator::addClientSession(QTcpSocket* socket) {
    Session* session = new Session{socket};
    m_clientSessions.push_back(session);
    connect(session, &Session::closed, [this, session] {
        m_clientSessions.removeOne(session);
        session->deleteLater();
    });
}

}  // namespace kygon::server
