#include "UserDto.hpp"

namespace kygon {

UserDto::UserDto(QObject* parent, QString username, bool streaming)
    : QObject{parent}, m_username{username}, m_streaming{streaming} {}

QByteArray UserDto::encode() const {
    QByteArray res;
    res.append(m_username.toUtf8());
    res.append(':');
    res.append(m_streaming ? "streaming" : "not_streaming");

    return res;
}

bool UserDto::decode(const QByteArray& input) {
    auto delimIndex = input.indexOf(':');
    if (delimIndex == -1 || delimIndex == input.size() - 1) {
        return false;
    }

    m_username = QString::fromUtf8(input.mid(0, delimIndex));
    // :not_streaming or :streaming
    m_streaming = input[delimIndex + 1] != 'n';
    return true;
}

}  // namespace kygon
