#include "Messenger.hpp"

#include <QAbstractSocket>
#include <QHostAddress>

#include "Utils.hpp"

namespace kygon {

namespace {

QByteArray prepareMessageHeader(MessageType type, MessageLengthUint length) {
    QByteArray res;
    res.append(reinterpret_cast<char*>(&type), sizeof(type));
    res.append(reinterpret_cast<char*>(&length), sizeof(length));
    return res;
}

}  // namespace

Messenger::Messenger(QAbstractSocket* socket) : m_socket{socket} {}

bool Messenger::sendSimpleMessage(MessageType type) {
    QByteArray byteArray = prepareMessageHeader(type, 0);
    if (m_socket->write(byteArray) != byteArray.size() || !m_socket->flush()) {
        qKCritical() << "Can't write to socket " << m_socket->peerAddress() << ":" << m_socket->peerPort();
        return false;
    }

    return true;
}

bool Messenger::sendUserAuth(const QString& username) {
    return sendStringMessage(MessageType::SendUserAuth, username);
}

bool Messenger::sendServerActiveUsers() {
    // TODO
    return false;
}

bool Messenger::sendUserMessage(const QString& userMessage) {
    return sendStringMessage(MessageType::SendUserMessage, userMessage);
}

bool Messenger::read(Message& message) {
    if (m_socket->read(reinterpret_cast<char*>(&message), kMessageHeaderSize) != kMessageHeaderSize) {
        qKCritical() << "Can't read message header for " << m_socket->peerAddress() << ":"
                     << m_socket->peerPort();
        return false;
    }

    if (message.length > 0) {
        message.value.resize(message.length);
        if (m_socket->read(message.value.data(), message.length) != message.length) {
            qKCritical() << "Can't read message body for " << m_socket->peerAddress() << ":"
                         << m_socket->peerPort();
            return false;
        }
    }

    return true;
}

bool Messenger::sendStringMessage(MessageType type, const QString& str) {
    QByteArray byteArray = prepareMessageHeader(type, str.toUtf8().size());
    byteArray.append(str.toUtf8());
    if (m_socket->write(byteArray) != byteArray.size() || !m_socket->flush()) {
        qKCritical() << "Can't write to socket " << m_socket->peerAddress() << ":" << m_socket->peerPort();
        return false;
    }
    return true;
}

}  // namespace kygon
