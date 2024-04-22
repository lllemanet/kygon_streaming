#include "ClientsMediator.hpp"

#include "ClientSession.hpp"
#include "common/Utils.hpp"

namespace kygon::server {

ClientsMediator::ClientsMediator(QObject* parent) : QObject{parent} {}

void ClientsMediator::addClientSession(QTcpSocket* socket) {
    ClientSession* session = new ClientSession{*socket};
    m_connectedSessions.push_back(session);
    connect(session, &ClientSession::sessionAuth, this, &ClientsMediator::onSessionAuth);
    connect(session, &ClientSession::closed, this, &ClientsMediator::onSessionClosed);
}

void ClientsMediator::onSessionAuth() {
    ClientSession* session = dynamic_cast<ClientSession*>(QObject::sender());
    m_connectedSessions.removeOne(session);
    m_authenticatedSessions.push_back(session);
    notifyActiveUsersChanged();
}

void ClientsMediator::onSessionClosed() {
    ClientSession* session = dynamic_cast<ClientSession*>(QObject::sender());
    if (m_authenticatedSessions.removeOne(session)) {
        notifyActiveUsersChanged();
    }
    m_connectedSessions.removeOne(session);
    session->deleteLater();
    qKDebug() << "ChatManager closed: " << session->toString();
}

void ClientsMediator::notifyActiveUsersChanged() {
    // TODO: 1. Consider ServerState and ServerStateChange and serialization
    QByteArray activeUsers;
    for (ClientSession* session : m_authenticatedSessions) {
        activeUsers.append(session->getUsername());
        activeUsers.append(',');
    }
    for (ClientSession* session : m_authenticatedSessions) {
        session->sendActiveUsers(activeUsers);
    }
}

}  // namespace kygon::server
