#pragma once

#include <QObject>
#include <QTcpSocket>

namespace kygon::client {

/**
 * @brief Manages all interaction with the server. It's "Model" for "View" discarding Controller.
 *
 */
class ChatManager : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ChatManager)

public:
    ChatManager(QObject* parent = nullptr);
    virtual ~ChatManager() = default;

    bool init(QHostAddress address, quint16 port, QString username);

Q_SIGNALS:
    void activeUsersChanged(const QList<QByteArray>& activeUsers);
    void closed();

private Q_SLOTS:
    void onConnected();
    void handleMessage();

private:
    QTcpSocket m_socket;
    bool m_authenticated;
    QString m_username;
    QList<QByteArray> m_activeUsers;
    QByteArray m_buffer;
};

}  // namespace kygon::client
