#pragma once

#include <QObject>
#include <QString>

namespace kygon {

class UserDto : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString username READ username)
    Q_PROPERTY(bool streaming READ streaming)

public:
    UserDto(QObject* parent = nullptr, QString username = "", bool streaming = false);

    QByteArray encode() const;
    bool decode(const QByteArray& input);

    QString username() const { return m_username; }
    bool streaming() const { return m_streaming; }

private:
    QString m_username;
    bool m_streaming;
};

}  // namespace kygon
