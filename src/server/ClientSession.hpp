#pragma once

#include <QObject>
#include <QString>

class QAbstractSocket;

namespace kygon::server {

/**
 * @brief Client session. Implements protocol interactions.
 *
 */
class ClientSession : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ClientSession)

public:
    ClientSession(QAbstractSocket& socket, QObject* parent = nullptr);
    virtual ~ClientSession() = default;

    QString toString();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void handleMessage();

private:
    QAbstractSocket& m_socket;
    bool m_authenticated;
    QByteArray m_buffer;
};

}  // namespace kygon::server
