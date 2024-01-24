#include "ServerSession.hpp"

#include "common/Protocol.hpp"
#include "common/Utils.hpp"

namespace kygon::client {

ServerSession::ServerSession(QObject* parent) : QObject{parent}, m_socket{}, m_authenticated{false} {}

bool ServerSession::init(QHostAddress address, quint16 port, QString username) {
    m_username = username;
    m_socket.connectToHost(address, port);
    connect(&m_socket, &QTcpSocket::connected, this, &ServerSession::onConnected);
    connect(&m_socket, &QTcpSocket::readyRead, this, &ServerSession::handleMessage);
    connect(&m_socket, &QTcpSocket::errorOccurred, this, &ServerSession::closed);
    connect(&m_socket, &QTcpSocket::disconnected, this, &ServerSession::closed);
    return true;
}

void ServerSession::onConnected() {
    if (!sendMessage(m_socket, MessageType::SendUserAuth, m_username.toUtf8())) {
        qKCritical() << "Can't send user auth";
        Q_EMIT closed();
    }
}

void ServerSession::handleMessage() {
    MessageHeader header;
    if (!receiveMessage(m_socket, header, m_buffer)) {
        qKCritical() << "Can't read message header";
        Q_EMIT closed();
        return;
    }

    if (!m_authenticated) {
        if (header.type != MessageType::RespUserAuth) {
            qKCritical() << "Expected auth response";
            Q_EMIT closed();
            return;
        }

        // Split comma-separated usernames
        m_activeUsers = m_buffer.split(',');
        Q_EMIT sessionStarted(m_activeUsers);
    }
}

}  // namespace kygon::client
