import QtQuick

import kygon

Rectangle {
    property int usernameFontPixelSize: 16

    color: "#E0E0E0"
    radius: 10

    ListView {
        anchors.fill: parent
        spacing: 5

        model: ChatManager.activeUsers
        delegate: Rectangle {

            height: usernameFontPixelSize + 5
            width: parent.width

            Text {
                anchors.centerIn: parent
                text: model.username
                font.pixelSize: model.streaming ? usernameFontPixelSize + 10 : usernameFontPixelSize
            }
        }
    }
}


