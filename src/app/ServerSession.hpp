#pragma once

#include <QObject>
#include <QTcpSocket>

#include "common/Messenger.hpp"

namespace kygon::client {

class ServerSession : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ServerSession)

public:
    ServerSession(QObject* parent = nullptr);
    virtual ~ServerSession() = default;

    bool init(QHostAddress address, quint16 port);

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void handleMessage();

private:
    QTcpSocket m_socket;
    Messenger m_messenger;
    bool m_authenticated;
};

}  // namespace kygon::client
