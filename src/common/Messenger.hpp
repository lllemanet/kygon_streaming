#pragma once

#include <QByteArray>
#include <QtGlobal>

class QAbstractSocket;

namespace kygon {

// TODO: protocol description
enum class MessageType : quint16 {
    Unknown                    = 0x0,
    RespMask                   = 1 << 15,  // All response messages have 1 << 15 bit set
    SendUserAuth               = 0x1,
    RespUserAuth               = RespMask | SendUserAuth,
    SendServerActiveUsers      = 0x2,
    SendUserMessage            = 0x3,
    RespUserMessage            = RespMask | SendUserMessage,
    SendServerBroadcastMessage = 0x4
};

using MessageLengthUint = quint32;

#pragma pack(push, 1)
struct Message {
    MessageType type;
    MessageLengthUint length;  // in bytes
    QByteArray value;
};
#pragma pack(pop)

constexpr size_t kMessageHeaderSize = offsetof(Message, value);

class Messenger {
    Q_DISABLE_COPY_MOVE(Messenger)

public:
    /**
     * @brief Construct a new Messenger object.
     *
     * @param socket socket should outlive Messenger object.
     */
    Messenger(QAbstractSocket* socket);

    bool sendSimpleMessage(MessageType type);
    bool sendUserAuth(const QString& username);
    bool sendUserMessage(const QString& userMessage);
    bool sendServerActiveUsers(/*TODO list of users*/);
    bool read(Message& message);

private:
    bool sendStringMessage(MessageType type, const QString& str);

    QAbstractSocket* m_socket;
};

}  // namespace kygon
