#pragma once

#include <QtQml/qqmlregistration.h>

#include <QObject>
#include <QTcpSocket>
#include <QList>
#include <QQmlListProperty>

#include "common/UserDto.hpp"

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

    Q_PROPERTY(QQmlListProperty<UserDto> activeUsers READ activeUsers NOTIFY activeUsersChanged FINAL)
    Q_PROPERTY(QList<QByteArray> userMessages READ userMessages NOTIFY userMessagesChanged FINAL)

public:
    ChatManager(QObject* parent = nullptr);
    virtual ~ChatManager() = default;

    // Q_PROPERTY handlers
    QQmlListProperty<UserDto> activeUsers();
    QList<QByteArray> userMessages() const;
Q_SIGNALS:
    void activeUsersChanged();
    void userMessagesChanged();

Q_SIGNALS:
    void connectionError(QAbstractSocket::SocketError error);

public Q_SLOTS:
    bool init(QString address, quint16 port, QString username);
    void sendUserMessage(QString message);
    void startStream();

private Q_SLOTS:
    void onConnected();
    void handleMessage();

private:
    QTcpSocket m_socket;
    bool m_authenticated;
    QString m_username;
    QList<UserDto*> m_activeUsers;
    QList<QByteArray> m_userMessages;
    QByteArray m_buffer;
};

}  // namespace kygon::client
