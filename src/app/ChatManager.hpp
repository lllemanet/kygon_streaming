#pragma once

#include <QtQml/qqmlregistration.h>

#include <QObject>
#include <QTcpSocket>

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

    Q_PROPERTY(QList<QByteArray> activeUsers READ activeUsers NOTIFY activeUsersChanged FINAL)

public:
    ChatManager(QObject* parent = nullptr);
    virtual ~ChatManager() = default;

    QList<QByteArray> activeUsers() const;

Q_SIGNALS:
    void connectionError(QAbstractSocket::SocketError error);
    void activeUsersChanged();

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
