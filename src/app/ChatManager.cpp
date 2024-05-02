#include "ChatManager.hpp"

#include "common/Protocol.hpp"
#include "common/Utils.hpp"

namespace kygon::client {

namespace {
// TODO: we need to use our own enum for our own network errors
constexpr auto kNetworkError = QAbstractSocket::SocketError::NetworkError;
}

ChatManager::ChatManager(QObject* parent) : QObject{parent}, m_socket{}, m_authenticated{false} {}

bool ChatManager::init(QString address, quint16 port, QString username) {
    m_username = username;
    m_socket.connectToHost(QHostAddress{address}, port);
    connect(&m_socket, &QTcpSocket::connected, this, &ChatManager::onConnected);
    connect(&m_socket, &QTcpSocket::readyRead, this, &ChatManager::handleMessage);
    connect(&m_socket, &QTcpSocket::errorOccurred, this, &ChatManager::connectionError);
    connect(&m_socket, &QTcpSocket::disconnected, this, [this] { connectionError(kNetworkError); });
    return true;
}

void ChatManager::onConnected() {
    if (!sendMessage(m_socket, MessageType::SendUserAuth, m_username.toUtf8())) {
        qKCritical() << "Can't send user auth";
        Q_EMIT connectionError(kNetworkError);
    }
}

void ChatManager::handleMessage() {
    MessageHeader header;
    if (!receiveMessage(m_socket, header, m_buffer)) {
        qKCritical() << "Can't read message header";
        Q_EMIT connectionError(kNetworkError);
        return;
    }

    if (!m_authenticated) {
        if (header.type != MessageType::RespUserAuth || m_buffer[0] != ResultCode::Ok) {
            qKCritical() << "Authentication failed";
            Q_EMIT connectionError(kNetworkError);
            return;
        }
        m_authenticated = true;
    }

    if (header.type == MessageType::SendActiveUsers) {
        m_activeUsers = m_buffer.split(',');
        Q_EMIT activeUsersChanged(m_activeUsers);
    }
}

}  // namespace kygon::client
