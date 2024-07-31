import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import kygon

Rectangle {
    id: root
    color: "#E0E0E0"

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        ActiveUsers {
            id: activeUsers
            Layout.preferredWidth: parent.width
            Layout.fillHeight: true
        }

        Button {
            id: streamControl
            text: "Start Stream"
            Layout.preferredWidth: parent.width
            onClicked: {
                ChatManager.startStream();
            }
        }
    }
}
