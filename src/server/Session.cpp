#include "Session.hpp"

#include <QAbstractSocket>
#include <QHostAddress>

#include "common/Protocol.hpp"
#include "common/Utils.hpp"

namespace kygon::server {

Session::Session(QAbstractSocket& socket, QObject* parent)
    : QObject{parent}, m_socket{socket}, m_authenticated{false} {
    m_socket.setParent(this);
    connect(&m_socket, &QAbstractSocket::readyRead, this, &Session::handleMessage);
    connect(&m_socket, &QAbstractSocket::errorOccurred, this, &Session::closed);
    connect(&m_socket, &QAbstractSocket::disconnected, this, &Session::closed);
}

QString Session::toString() {
    return QString(m_socket.peerAddress().toString() + ":" + QString::number(m_socket.peerPort()));
}

void Session::handleMessage() {
    MessageHeader header;
    if (!receiveMessage(m_socket, header, m_buffer)) {
        qKCritical() << "Can't read message header, clossing session";
        Q_EMIT closed();
        return;
    }

    if (!m_authenticated) {
        if (header.type != MessageType::SendUserAuth) {
            qKCritical() << "User didn't authenticated, closing session";
            Q_EMIT closed();
            return;
        }

        if (!sendMessage(m_socket, MessageType::RespUserAuth)) {
            qKCritical() << "Auth response failed, closing session";
            Q_EMIT closed();
            return;
        }

        qKDebug() << "Client authenticated: username=" << m_buffer;
    }
}

}  // namespace kygon::server
