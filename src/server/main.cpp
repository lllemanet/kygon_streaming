#include <QTcpServer>
#include <QTcpSocket>

#include "common/Utils.hpp"

using namespace kygon;

const QHostAddress kServerAddress{"127.0.0.1"};
const uint16_t kServerPort{29118};

int main(int argc, char* argv[]) {
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    if (argc > 1) {
        // Client
        QTcpSocket tcpSocket;
        tcpSocket.connectToHost(kServerAddress, kServerPort);
        tcpSocket.waitForConnected();
        if (tcpSocket.state() == QAbstractSocket::SocketState::ConnectedState) {
            qKDebug() << "Connected successfully";
        } else {
            qKCritical() << "Can't connect to " << kServerAddress.toString() << ":" << kServerPort;
        }
    } else {
        // Server
        QTcpServer tcpServer;
        if (!tcpServer.listen(kServerAddress, kServerPort)) {
            qKCritical() << "Can't listen on " << kServerAddress.toString() << ":" << kServerPort;
            return -1;
        }

        if (tcpServer.waitForNewConnection(100000)) {
            qKDebug() << "Received new connection!";
            QTcpSocket* serverSocket = tcpServer.nextPendingConnection();
            serverSocket->close();
        }
    }

    return 0;
}
