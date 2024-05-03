#include "ClientSession.hpp"

#include <QAbstractSocket>
#include <QHostAddress>

#include "common/Protocol.hpp"
#include "common/Utils.hpp"

namespace kygon::server {

ClientSession::ClientSession(QAbstractSocket& socket, QObject* parent)
    : QObject{parent}, m_socket{socket} {
    m_socket.setParent(this);
    connect(&m_socket, &QAbstractSocket::readyRead, this, &ClientSession::handleMessage);
    connect(&m_socket, &QAbstractSocket::errorOccurred, this, &ClientSession::closed);
    connect(&m_socket, &QAbstractSocket::disconnected, this, &ClientSession::closed);
}

void ClientSession::sendActiveUsers(const QByteArray& activeUsers) {
    if (!sendMessage(m_socket, MessageType::SendActiveUsers, activeUsers)) {
        qKCritical() << "Can't send SendActiveUsers, closing session";
        Q_EMIT closed();
    }
}

void ClientSession::broadcastUserMessage(const QByteArray &msg)
{
    if (!sendMessage(m_socket, MessageType::SendBroadcastMessage, msg)) {
        qKCritical() << "Can't send SendBroadcastMessage, closing session";
        Q_EMIT closed();
    }
}

QByteArray ClientSession::getUsername() {
    return m_username;
}

QString ClientSession::toString() {
    return QString(m_socket.peerAddress().toString() + ":" + QString::number(m_socket.peerPort()));
}

void ClientSession::handleMessage() {
    MessageHeader header;
    if (!receiveMessage(m_socket, header, m_buffer)) {
        qKCritical() << "Can't read message header, closing session";
        Q_EMIT closed();
        return;
    }

    // if not authenticated
    if (m_username.size() == 0) {
        if (header.type != MessageType::SendUserAuth) {
            qKCritical() << "User didn't authenticated, closing session";
            Q_EMIT closed();
            return;
        }

        if (!sendMessage(m_socket, MessageType::RespUserAuth, QByteArray{1, ResultCode::Ok})) {
            qKCritical() << "Can't respond authenticated succeed";
            Q_EMIT closed();
            return;
        }

        m_username = m_buffer;
        qKDebug() << "Client started authentication: username=" << m_username;

        Q_EMIT sessionAuth();
    }

    if (header.type == MessageType::SendUserMessage) {
        m_buffer.prepend(m_username + ": ");
        Q_EMIT userMessageReceived(m_buffer);
    }
}

}  // namespace kygon::server
