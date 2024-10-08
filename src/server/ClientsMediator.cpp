#include "ClientsMediator.hpp"

#include "ClientSession.hpp"
#include "common/UserDto.hpp"
#include "common/Utils.hpp"

namespace kygon::server {

ClientsMediator::ClientsMediator(QObject* parent) : QObject{parent} {}

void ClientsMediator::addClientSession(QTcpSocket* socket) {
    // TODO: this socket can't be used from other thread (see QTcpServer::nextPendingConnection)
    ClientSession* session = new ClientSession{*socket, this};
    m_connectedSessions.push_back(session);
    connect(session, &ClientSession::sessionAuth, this, &ClientsMediator::onSessionAuth);
    connect(session, &ClientSession::startedStreaming, this, &ClientsMediator::notifyActiveUsersChanged);
    connect(session, &ClientSession::userMessageReceived, this, &ClientsMediator::onUserMessageReceived);
    connect(session, &ClientSession::closed, this, &ClientsMediator::onSessionClosed);
}

void ClientsMediator::onSessionAuth() {
    ClientSession* session = dynamic_cast<ClientSession*>(QObject::sender());
    m_connectedSessions.removeOne(session);
    for (auto* s : m_authenticatedSessions) {
        if (s->getUsername() == session->getUsername()) {
            kLog(Warning) << "Sessions with username=" << session->getUsername() << " already exists..."
                          << "closing session";
            session->respUserAuth(false);
            Q_EMIT session->closed();
            return;
        }
    }

    kLog(Debug) << "Session with username=" << session->getUsername() << " is authenticated";
    session->respUserAuth(true);
    m_authenticatedSessions.push_back(session);
    notifyActiveUsersChanged();
}

void ClientsMediator::onUserMessageReceived(const QByteArray& userMessage) {
    for (ClientSession* session : m_authenticatedSessions) {
        session->broadcastUserMessage(userMessage);
    }
}

void ClientsMediator::onSessionClosed() {
    ClientSession* session = dynamic_cast<ClientSession*>(QObject::sender());
    if (m_authenticatedSessions.removeOne(session)) {
        notifyActiveUsersChanged();
    }
    m_connectedSessions.removeOne(session);
    session->deleteLater();
}

void ClientsMediator::notifyActiveUsersChanged() {
    // TODO: 1. Consider ServerState and ServerStateChange and serialization
    QByteArray activeUsers;
    for (ClientSession* session : m_authenticatedSessions) {
        UserDto userDto{this, session->getUsername(), session->isStreaming()};
        activeUsers.append(userDto.encode());
        activeUsers.append(',');
    }
    activeUsers.removeLast();
    for (ClientSession* session : m_authenticatedSessions) {
        session->sendActiveUsers(activeUsers);
    }
}

}  // namespace kygon::server
