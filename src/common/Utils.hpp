#pragma once

#include <QDebug>

#define qKDebug() qDebug().noquote().nospace()
#define qKCritical() qCritical().noquote().nospace()
