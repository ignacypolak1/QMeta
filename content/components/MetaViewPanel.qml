import Qt.labs.platform
import QtQuick 6.2
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: metaViewPanel

    Layout.fillHeight: true
    Layout.fillWidth: true
    Layout.preferredWidth: 3
    color: Qt.rgba(0, 0, 0, 0.2)
    border.color: Qt.rgba(0.549, 0.549, 0.549, 0.6)
    border.width: 1

    MetaListView {
        id: metaListView
    }

}
