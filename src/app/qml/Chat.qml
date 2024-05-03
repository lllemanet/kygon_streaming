import QtQuick
import QtQuick.Layouts

Rectangle {
    id: root
    color: "#CCFFCC"
    radius: 10

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        UserMessages {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        MessageInput {
            Layout.fillWidth: true
            Layout.preferredHeight: fontPixelSize * 3
        }
    }
}
