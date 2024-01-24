#pragma once

#include <QGuiApplication>

#include "Session.hpp"

namespace kygon::client {

class UiApplication : public QGuiApplication {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(UiApplication)

public:
    UiApplication(int argc, char* argv[]);
    virtual ~UiApplication() = default;

    bool init();

private:
    Session m_session;
};

}  // namespace kygon::client
