#pragma once

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "ChatManager.hpp"

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
    ChatManager m_chatManager;
};

}  // namespace kygon::client
