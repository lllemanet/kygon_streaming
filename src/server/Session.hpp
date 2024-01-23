#pragma once

#include <QObject>
#include <QString>

#include "common/Messenger.hpp"

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
    Session(QAbstractSocket* socket, QObject* parent = nullptr);
    virtual ~Session() = default;

    QString toString();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void handleMessage();

private:
    QAbstractSocket* m_socket;
    Messenger m_messenger;
    bool m_authenticated;
};

}  // namespace kygon::server
