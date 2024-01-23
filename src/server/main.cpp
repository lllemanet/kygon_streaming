#include <QTcpSocket>
#include <thread>

#include "Application.hpp"
#include "common/Messenger.hpp"
#include "common/Utils.hpp"

void stubAuth(QTcpSocket& socket) {
    kygon::Messenger messenger{&socket};

    messenger.sendUserAuth("mynameis");
    socket.waitForReadyRead(1000);
    kygon::Message msg;
    messenger.read(msg);
    if (msg.type == kygon::MessageType::RespUserAuth) {
        qKDebug() << "read successfully";
    }
}

int main(int argc, char* argv[]) {
    kygon::server::Application app{argc, argv};

    if (argc == 1) {
        // Temporary client for tests
        QTcpSocket tcpSocket;
        tcpSocket.connectToHost(QHostAddress{"127.0.0.1"}, 29118);
        tcpSocket.waitForConnected();
        if (tcpSocket.state() == QAbstractSocket::SocketState::ConnectedState) {
            qKDebug() << "Connected successfully";
            stubAuth(tcpSocket);
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
