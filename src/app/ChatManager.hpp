#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QtQml/qqmlregistration.h>

namespace kygon::client {

/**
 * @brief Controller Facade for QML-side.
 *
 */
class ChatManager : public QObject {
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT
    Q_DISABLE_COPY_MOVE(ChatManager)

public:
    ChatManager(QObject* parent = nullptr);
    virtual ~ChatManager() = default;

Q_SIGNALS:
    void connectionError(QAbstractSocket::SocketError error);
    void activeUsersChanged(const QList<QByteArray>& activeUsers);

public Q_SLOTS:
    bool init(QString address, quint16 port, QString username);

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
