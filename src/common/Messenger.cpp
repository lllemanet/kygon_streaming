#include "Messenger.hpp"

#include <QAbstractSocket>

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

bool Messenger::sendUserAuth(const QString& username) {
    QByteArray byteArray = prepareMessageHeader(MessageType::SendUserAuth, username.toUtf8().size());
    byteArray.append(username.toUtf8());
    TEST_AND_RETURN_FALSE(m_socket->write(byteArray) == byteArray.size());
    return true;
}

bool Messenger::sendServerActiveUsers() {
    // TODO
    return false;
}

bool Messenger::sendUserMessage(const QString& userMessage) {
    QByteArray byteArray = prepareMessageHeader(MessageType::SendUserMessage, userMessage.toUtf8().size());
    byteArray.append(userMessage.toUtf8());
    TEST_AND_RETURN_FALSE(m_socket->write(byteArray) == byteArray.size());
    return true;
}

bool Messenger::read(Message& message) {
    TEST_AND_RETURN_FALSE(m_socket->read(reinterpret_cast<char*>(&message), offsetof(Message, value)) ==
                          offsetof(Message, value));
    message.value.resize(message.length);
    TEST_AND_RETURN_FALSE(m_socket->read(message.value.data(), message.length) == message.length);
    return true;
}

}  // namespace kygon
