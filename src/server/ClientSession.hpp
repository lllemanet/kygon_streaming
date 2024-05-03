#pragma once

#include <QObject>
#include <QString>

class QAbstractSocket;

namespace kygon::server {

/**
 * @brief Client session. Implements protocol.
 *
 */
class ClientSession : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ClientSession)

public:
    ClientSession(QAbstractSocket& socket, QObject* parent = nullptr);
    virtual ~ClientSession() = default;

    void sendActiveUsers(const QByteArray& activeUsers);
    void broadcastUserMessage(const QByteArray& msg);

    QByteArray getUsername();
    QString toString();

Q_SIGNALS:
    void sessionAuth();
    void userMessageReceived(const QByteArray& msg);
    void closed();

private Q_SLOTS:
    void handleMessage();

private:
    QAbstractSocket& m_socket;
    QByteArray m_username;
    QByteArray m_buffer;
};

}  // namespace kygon::server
