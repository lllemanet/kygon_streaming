#pragma once

#include <QObject>
#include <QTcpSocket>

namespace kygon::client {

// TODO: come up with better name
class Session : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Session)

public:
    Session(QObject* parent = nullptr);
    virtual ~Session() = default;

    bool init(QHostAddress address, quint16 port, QString username);

Q_SIGNALS:
    void sessionStarted(const QList<QByteArray>& activeUsers);
    void closed();

private Q_SLOTS:
    void onConnected();
    void handleMessage();

private:
    QTcpSocket m_socket;
    QString m_username;
    QList<QByteArray> m_activeUsers;
    QByteArray m_buffer;
    bool m_authenticated;
};

}  // namespace kygon::client
