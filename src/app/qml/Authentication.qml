import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    property alias serverAddress: serverAddressTextField.text
    property alias username: usernameTextField.text
    property alias password: passwordTextField.text
    signal loginRequest(serverAddress: string, username: string, password: string)

    anchors.centerIn: parent
    height: parent.height * 0.5
    width: parent.width * 0.5
    color: "#E0E0E0"
    radius: 10

    Column {
        anchors.centerIn: parent
        spacing: 20

        TextField {
            id: serverAddressTextField
            text: "127.0.0.1:29118"
        }

        TextField {
            id: usernameTextField
            placeholderText: "Username"
        }

        TextField {
            id: passwordTextField
            placeholderText: "Password"
        }

        Button {
            id: loginButton
            text: "Login"
            width: passwordTextField.width
            onClicked: root.loginRequest(root.serverAddress, root.username, root.password);
        }
    }
}
