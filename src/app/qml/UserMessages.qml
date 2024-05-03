import QtQuick
import QtQuick.Controls

import kygon

Rectangle {
    property int userMessageFontPixelSize: 16

    color: "#E0E0E0"
    radius: 10

    ScrollView {
        anchors.fill: parent

        ListView {
            anchors.fill: parent
            spacing: 2

            model: ChatManager.userMessages
            delegate: Rectangle {
                required property string modelData

                height: messageText.height
                width: parent.width

                TextArea {
                    id: messageText
                    anchors.left: parent.left
                    text: modelData
                    font.pixelSize: userMessageFontPixelSize
                    wrapMode: TextEdit.Wrap
                }
            }
        }
    }
}


