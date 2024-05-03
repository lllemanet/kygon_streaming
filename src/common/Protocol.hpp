#pragma once

#include <QByteArray>
#include <QtGlobal>

class QAbstractSocket;

namespace kygon {

// TODO: protocol description
enum MessageType : quint16 {
    Unknown              = 0x0,
    ClientChannel        = 0 << 15,
    ServerChannel        = 1 << 15,
    SendUserAuth         = ClientChannel | 0x1,
    RespUserAuth         = ClientChannel | 0x2,
    SendUserMessage      = ClientChannel | 0x3,
    SendActiveUsers      = ServerChannel | 0x1,
    SendBroadcastMessage = ServerChannel | 0x3,
};

enum ResultCode : char { UnknownError = 0, Ok = 1, InvalidUsername = 2 };

using MessageLengthUint = quint32;

#pragma pack(push, 1)
struct MessageHeader {
    MessageType type;
    MessageLengthUint length;  // in bytes
};
#pragma pack(pop)

// TODO: try more oop
bool sendMessage(QAbstractSocket& socket, MessageType type, const QByteArray& body = QByteArray{});
bool receiveMessage(QAbstractSocket& socket, MessageHeader& header, QByteArray& body);

}  // namespace kygon
