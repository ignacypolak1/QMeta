import Qt.labs.platform
import QtQuick 6.2
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    anchors.fill: parent
    spacing: 0

    Rectangle {
        id: selectionPanel

        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.preferredWidth: 2
        color: Qt.rgba(0, 0, 0, 0.3)
        border.color: Qt.rgba(0.549, 0.549, 0.549, 0.6)
        border.width: 1

        ListView {
            id: fileListView

            Keys.onPressed: (event) => {
                if (event.key === Qt.Key_W || event.key === Qt.Key_Up) {
                    if (currentIndex > 0)
                        currentIndex--;

                    event.accepted = true;
                } else if (event.key === Qt.Key_S || event.key === Qt.Key_Down) {
                    if (currentIndex < count - 1)
                        currentIndex++;

                    event.accepted = true;
                } else if (event.key === Qt.Key_Space) {
                    var selectedItem = fileModel.get(fileListView.currentIndex);
                    if (selectedItem)
                        controller.CR(selectedItem.path);

                    event.accepted = true;
                }
            }
            anchors.fill: parent
            model: fileModel
            focus: true

            delegate: Rectangle {
                width: parent.width
                height: 30
                color: ListView.isCurrentItem ? Qt.rgba(0, 0, 0.6, 0.6) : Qt.rgba(0, 0, 0, 0.3)
                border.color: Qt.rgba(0.549, 0.549, 0.549, 0.6)
                border.width: 1

                Row {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 0
                    leftPadding: 5

                    Text {
                        text: name
                        color: "white"
                    }

                }

            }

        }

    }

}
