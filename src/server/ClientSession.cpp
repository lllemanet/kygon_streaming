#include "ClientSession.hpp"

#include <QAbstractSocket>
#include <QHostAddress>

#include "common/Protocol.hpp"
#include "common/Utils.hpp"

namespace kygon::server {

ClientSession::ClientSession(QAbstractSocket& socket, QObject* parent)
    : QObject{parent}, m_socket{socket}, m_authenticated{false}, m_streaming{false} {
    m_socket.setParent(this);
    connect(&m_socket, &QAbstractSocket::readyRead, this, &ClientSession::handleMessage);
    connect(&m_socket, &QAbstractSocket::errorOccurred, this, &ClientSession::closed);
    connect(&m_socket, &QAbstractSocket::disconnected, this, &ClientSession::closed);
}

void ClientSession::respUserAuth(bool success) {
    ResultCode responseCode = success ? ResultCode::Ok : ResultCode::InvalidUsername;
    if (!sendMessage(m_socket, MessageType::RespUserAuth, QByteArray{1, responseCode})) {
        kLog(Critical) << "Can't respond authentication result";
        Q_EMIT closed();
        return;
    }
    m_authenticated = success;
}

void ClientSession::sendActiveUsers(const QByteArray& activeUsers) {
    if (!sendMessage(m_socket, MessageType::SendActiveUsers, activeUsers)) {
        kLog(Critical) << "Can't send SendActiveUsers, closing session";
        Q_EMIT closed();
    }
}

void ClientSession::broadcastUserMessage(const QByteArray& msg) {
    if (!sendMessage(m_socket, MessageType::SendBroadcastMessage, msg)) {
        kLog(Critical) << "Can't send SendBroadcastMessage, closing session";
        Q_EMIT closed();
    }
}

QByteArray ClientSession::getUsername() {
    return m_username;
}

bool ClientSession::isStreaming() {
    return m_streaming;
}

QString ClientSession::toString() {
    return QString(m_socket.peerAddress().toString() + ":" + QString::number(m_socket.peerPort()));
}

void ClientSession::handleMessage() {
    MessageHeader header;
    if (!receiveMessage(m_socket, header, m_buffer)) {
        kLog(Critical) << "Can't read message header, closing session";
        Q_EMIT closed();
        return;
    }

    // First session must be authenticated
    if (!m_authenticated) {
        if (header.type != MessageType::SendUserAuth) {
            kLog(Critical) << "User didn't authenticated, closing session";
            Q_EMIT closed();
            return;
        }

        m_username = m_buffer;
        kLog(Debug) << "Client started authentication: username=" << m_username;

        Q_EMIT sessionAuth();
    }

    switch (header.type) {
        case MessageType::SendUserMessage: {
            m_buffer.prepend(m_username + ": ");
            Q_EMIT userMessageReceived(m_buffer);
            break;
        }
        case MessageType::SendStartStream: {
            m_streaming = true;
            Q_EMIT startedStreaming();
        }
    }
}

}  // namespace kygon::server
