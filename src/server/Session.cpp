#include "Session.hpp"

#include "common/Utils.hpp"

namespace kygon::server {

Session::Session(QAbstractSocket* socket, QObject* parent) : m_socket{socket}, QObject{parent} {
    m_socket->setParent(this);
    connect(socket, &QAbstractSocket::disconnected, this, &Session::closed);
}

}  // namespace kygon::server
