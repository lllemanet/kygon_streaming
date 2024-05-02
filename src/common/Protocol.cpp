#include "Protocol.hpp"

#include <QAbstractSocket>
#include <QHostAddress>

namespace kygon {

bool sendMessage(QAbstractSocket& socket, MessageType type, const QByteArray& body) {
    QByteArray messageBuffer;
    messageBuffer.append(reinterpret_cast<char*>(&type), sizeof(type));
    MessageLengthUint length = body.size();
    messageBuffer.append(reinterpret_cast<char*>(&length), sizeof(length));
    messageBuffer.append(body);

    return (socket.write(messageBuffer) == messageBuffer.size() && socket.flush());
}

bool receiveMessage(QAbstractSocket& socket, MessageHeader& res, QByteArray& buffer) {
    if (socket.read(reinterpret_cast<char*>(&res), sizeof(MessageHeader)) != sizeof(MessageHeader)) {
        return false;
    }

    // TODO: very very bad, consider how to adapt QByteArray for your purposes
    buffer.resize(res.length);

    return (socket.read(buffer.data(), res.length) == res.length);
}

}  // namespace kygon
