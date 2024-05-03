import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import kygon

Item {
    property int fontPixelSize: 16

    RowLayout {
        anchors.fill: parent
        spacing: 10

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            ScrollBar.vertical.policy: ScrollBar.AlwaysOff

            TextArea {
                id: messageTextArea
                placeholderText: "Your Message"
                wrapMode: TextEdit.Wrap
                font.pixelSize: fontPixelSize
                Keys.onReturnPressed: sendUserMessage();
            }
        }

        Button {
            Text {
                anchors.centerIn: parent
                font.pixelSize: fontPixelSize
                text: "Send"
            }

            Layout.preferredWidth: 50
            Layout.preferredHeight: 50

            onClicked: sendUserMessage();
        }
    }

    function sendUserMessage() {
        ChatManager.sendUserMessage(messageTextArea.text);
        messageTextArea.text = "";
    }
}
