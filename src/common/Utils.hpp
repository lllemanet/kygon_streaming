#pragma once

#include <QDebug>

namespace kygon {

// TODO: consider thread-safety
inline QDebug qKDebug() {
    static QDebug qDebugSingleton = qDebug().noquote().nospace();
    return qDebugSingleton;
}

inline QDebug qKCritical() {
    static QDebug qCriticalSingleton = qCritical().noquote().nospace();
    return qCriticalSingleton;
}

}  // namespace kygon
