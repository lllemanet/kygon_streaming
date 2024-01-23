#include "Session.hpp"

#include <QAbstractSocket>
#include <QHostAddress>

#include "common/Utils.hpp"

namespace kygon::server {

Session::Session(QAbstractSocket* socket, QObject* parent)
    : QObject{parent}, m_socket{socket}, m_messenger{m_socket}, m_authenticated{false} {
    m_socket->setParent(this);
    connect(socket, &QAbstractSocket::disconnected, this, &Session::closed);
    connect(socket, &QAbstractSocket::errorOccurred, this, &Session::closed);
    connect(socket, &QAbstractSocket::readyRead, this, &Session::handleMessage);
}

QString Session::toString() {
    return QString(m_socket->peerAddress().toString() + ":" + QString::number(m_socket->peerPort()));
}

void Session::handleMessage() {
    Message message;
    if (!m_messenger.read(message)) {
        qKCritical() << "Can't read message from client, closing session";
        Q_EMIT closed();
        return;
    }

    if (!m_authenticated) {
        if (message.type != MessageType::SendUserAuth) {
            qKCritical() << "User didn't authenticated, closing session";
            Q_EMIT closed();
            return;
        }

        if (!m_messenger.sendSimpleMessage(MessageType::RespUserAuth)) {
            qKCritical() << "Auth response failed, closing session";
            Q_EMIT closed();
            return;
        }

        qKDebug() << "Client authenticated: username=" << message.value;
    }
}

}  // namespace kygon::server
