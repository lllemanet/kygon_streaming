#pragma once

#include <QAbstractSocket>
#include <QObject>

namespace kygon::server {

/**
 * @brief Client session.
 *
 */
class Session : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Session)

public:
    Session(QAbstractSocket* socket, QObject* parent = nullptr);

Q_SIGNALS:
    void closed();

private:
    QAbstractSocket* m_socket;
};

}  // namespace kygon::server
