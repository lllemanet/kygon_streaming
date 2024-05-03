import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

import kygon

ApplicationWindow {
    id: root
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

    RowLayout {
        id: mainAreaLayout
        anchors.fill: parent

        visible: false
        spacing: 10

        ActiveUsers {
            Layout.preferredWidth: parent.width * 0.2
            Layout.fillHeight: true
        }

        Chat {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    MessageDialog {
        id: errorDialog
        title: "Error"
    }

    Connections {
        target: ChatManager

        function onConnectionError(socketError) {
            console.log("Connection error");
            errorDialog.text = "Connection error";
            errorDialog.visible = true;

        }

        function onActiveUsersChanged() {
            console.log("Connection established");
            authForm.visible = false;
            mainAreaLayout.visible = true;
        }

    }
}
