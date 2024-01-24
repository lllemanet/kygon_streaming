#pragma once

#include <QObject>
#include <QString>

class QAbstractSocket;

namespace kygon::server {

/**
 * @brief Client session.
 *
 */
class Session : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Session)

public:
    Session(QAbstractSocket& socket, QObject* parent = nullptr);
    virtual ~Session() = default;

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
