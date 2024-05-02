import QtQuick
import QtQuick.Controls
import kygon

ApplicationWindow {
    title: qsTr("kygon")
    visible: true
    visibility: Window.Maximized

    width: 1080
    height: 480

    Authentication {
        id: authForm
        onLoginRequest: (serverAddress, username, password) => {
                        var serverParts = serverAddress.split(":");
                        ChatManager.init(serverParts[0], serverParts[1], username);
                    }
    }

    Connections {
        target: ChatManager

        function onConnectionError(socketError) {
            console.log("Connection error");
        }

        function onActiveUsersChanged(activeUsers) {
            console.log("Connected to the server");
        }

    }
}
