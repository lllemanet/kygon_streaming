#include <QTcpSocket>

#include "Application.hpp"
#include "common/Utils.hpp"

int main(int argc, char* argv[]) {
    kygon::server::Application app{argc, argv};

    if (argc == 1) {
        // Client
        QTcpSocket tcpSocket;
        tcpSocket.connectToHost(QHostAddress{"127.0.0.1"}, 29118);
        tcpSocket.waitForConnected();
        if (tcpSocket.state() == QAbstractSocket::SocketState::ConnectedState) {
            qKDebug() << "Connected successfully";
        } else {
            qKCritical() << "Can't connect to 127.0.0.1:29118";
        }
    } else {
        if (!app.init()) {
            return -1;
        }
    }

    return app.exec();
}
