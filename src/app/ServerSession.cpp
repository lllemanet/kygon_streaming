#include "ServerSession.hpp"

#include "common/Utils.hpp"

namespace kygon::client {

ServerSession::ServerSession(QObject* parent)
    : QObject{parent}, m_messenger{&m_socket}, m_authenticated{false} {}

bool ServerSession::init(QHostAddress address, quint16 port) {
    m_socket.connectToHost(address, port);
    connect(&m_socket, &QTcpSocket::connected, this, &ServerSession::onConnected);
    connect(&m_socket, &QTcpSocket::readyRead, this, &ServerSession::handleMessage);
    return true;
}

void ServerSession::onConnected() {
    if (!m_messenger.sendUserAuth("username")) {
        qKCritical() << "Can't send user auth";
        Q_EMIT closed();
        return;
    }
}

void ServerSession::handleMessage() {
    Message message;
    if (!m_messenger.read(message)) {
        qKCritical() << "Can't read message";
        Q_EMIT closed();
        return;
    }

    if (!m_authenticated) {
        if (message.type != MessageType::RespUserAuth) {
            qKCritical() << "Expected auth here";
            Q_EMIT closed();
        }
        return;
    }
}

}  // namespace kygon::client
