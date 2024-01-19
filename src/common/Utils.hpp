#pragma once

#include <QDebug>

#define TEST_AND_RETURN_FALSE(_x)                               \
    do {                                                        \
        bool _success = static_cast<bool>(_x);                  \
        if (!_success) {                                        \
            qKCritical() << __FUNCTION__ << ":" #_x " failed."; \
            return false;                                       \
        }                                                       \
    } while (0)

#define qKDebug() qDebug().noquote().nospace()
#define qKCritical() qCritical().noquote().nospace()
