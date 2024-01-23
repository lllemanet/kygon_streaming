#pragma once

#include <QObject>
#include <QTcpSocket>
#include <Qlist>

namespace kygon::server {

class Session;

class ClientsMediator : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ClientsMediator)

public:
    ClientsMediator(QObject* parent = nullptr);
    virtual ~ClientsMediator() = default;

    /**
     * @brief ClientsMediator gets owneship of socket passed.
     *
     * @param socket New client socket.
     */
    void addClientSession(QTcpSocket* socket);

private:
    // Qt obligates us to use QObject::deleteLater on QTcpSocket::disconnected signal
    // (so we can't just destroy object and don't care but need pointer to call deleteLater
    // on). I can't come up with anything but storing list of pointers and rejecting RAII
    // by now.
    QList<Session*> m_clientSessions;
};

}  // namespace kygon::server
