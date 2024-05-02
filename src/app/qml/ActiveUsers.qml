import QtQuick

import kygon

Rectangle {
    property int usernameFontPixelSize: 14

    color: "#E0E0E0"
    radius: 10

    ListView {
        anchors.fill: parent
        spacing: 10

        model: ChatManager.activeUsers
        delegate: Rectangle {
            required property string modelData

            height: usernameFontPixelSize + 5
            width: parent.width

            Text {
                anchors.centerIn: parent
                text: modelData
                font.pixelSize: usernameFontPixelSize
            }
        }
    }
}


