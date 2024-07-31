#include "ChatManager.hpp"

#include "common/Protocol.hpp"
#include "common/Utils.hpp"

namespace kygon::client {

namespace {
// TODO: we need to use our own enum for our own network errors
constexpr auto kNetworkError = QAbstractSocket::SocketError::NetworkError;
}  // namespace

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

void ChatManager::sendUserMessage(QString message) {
    if (!sendMessage(m_socket, MessageType::SendUserMessage, message.toUtf8())) {
        kLog(Critical) << "Can't send user message";
        Q_EMIT connectionError(kNetworkError);
    }
}

void ChatManager::startStream() {
    if (!sendMessage(m_socket, MessageType::SendStartStream)) {
        kLog(Critical) << "Can't send start stream";
        Q_EMIT connectionError(kNetworkError);
    }
}

void ChatManager::onConnected() {
    if (!sendMessage(m_socket, MessageType::SendUserAuth, m_username.toUtf8())) {
        kLog(Critical) << "Can't send user auth";
        Q_EMIT connectionError(kNetworkError);
    }
}

void ChatManager::handleMessage() {
    while (m_socket.bytesAvailable()) {
        MessageHeader header;
        if (!receiveMessage(m_socket, header, m_buffer)) {
            kLog(Critical) << "Can't read message header";
            Q_EMIT connectionError(kNetworkError);
            return;
        }

        if (!m_authenticated) {
            if (header.type != MessageType::RespUserAuth || m_buffer[0] != ResultCode::Ok) {
                kLog(Critical) << "Authentication failed";
                Q_EMIT connectionError(kNetworkError);
                return;
            }
            kLog(Debug) << "User " << m_username << " is authenticated successfully";
            m_authenticated = true;
        }

        if (header.type == MessageType::SendActiveUsers) {
            qDeleteAll(m_activeUsers);
            m_activeUsers.clear();
            for (const auto& userBytes : m_buffer.split(',')) {
                UserDto* userDto = new UserDto(this);
                userDto->decode(userBytes);
                m_activeUsers.push_back(userDto);
            }
            Q_EMIT activeUsersChanged();
        }

        if (header.type == MessageType::SendBroadcastMessage) {
            m_userMessages.append(m_buffer);
            Q_EMIT userMessagesChanged();
        }
    }
}

QQmlListProperty<UserDto> ChatManager::activeUsers() {
    return QQmlListProperty<UserDto>(this, &m_activeUsers);
}

QList<QByteArray> ChatManager::userMessages() const {
    return m_userMessages;
}

}  // namespace kygon::client
