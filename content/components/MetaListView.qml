import Qt.labs.platform
import QtQuick 6.2
import QtQuick.Controls
import QtQuick.Layouts

ListView {
    id: metaListView

    anchors.fill: parent
    model: metaModel
    focus: true

    delegate: Item {
        width: parent.width
        height: 30

        Row {
            anchors.fill: parent
            spacing: 0

            Rectangle {
                width: parent.width / 2 - 90
                height: parent.height
                border.color: "grey"
                border.width: 1
                color: "transparent"

                Text {
                    text: key
                    anchors.centerIn: parent
                    color: "white"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }

            }

            Rectangle {
                width: parent.width / 2 + 90
                height: parent.height
                border.color: "grey"
                border.width: 1
                color: "transparent"

                Flickable {
                    id: flickableElement

                    width: parent.width - 60
                    height: parent.height
                    contentWidth: textElement.width
                    contentHeight: height
                    flickableDirection: Flickable.HorizontalFlick
                    clip: true
                    anchors.left: parent.left
                    anchors.leftMargin: 20

                    Text {
                        id: textElement

                        text: value
                        anchors.left: parent.left
                        color: "white"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                }

                CopyButton {
                    id: copyButton
                }

            }

        }

    }

}
