#pragma once

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "ServerSession.hpp"

namespace kygon::client {

class UiApplication : public QGuiApplication {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(UiApplication)

public:
    UiApplication(int argc, char* argv[]);
    virtual ~UiApplication() = default;

    bool init();

private:
    QQmlApplicationEngine m_qmlEngine;
    ServerSession m_session;
};

}  // namespace kygon::client
