#pragma once

#include <QDebug>

#define kLog(level) q ## level().noquote().nospace()
