import Qt.labs.platform
import QtQuick 6.2
import QtQuick.Controls
import QtQuick.Layouts

Button {
    width: 40
    height: parent.height
    anchors.left: flickableElement.right
    anchors.right: mapButton.right

    MouseArea {
        hoverEnabled: true
        anchors.fill: parent
        onClicked: {
            mapLoader.latitude = metaModel.getCoordinates().x;
            mapLoader.longitude = metaModel.getCoordinates().y;
            mapLoader.source = "MetaMap.qml";
        }
        onEntered: {
            copyIcon.opacity = 0.6;
        }
        onExited: {
            copyIcon.opacity = 1;
        }
    }

    Loader {
        id: mapLoader

        property double longitude
        property double latitude

        onLoaded: {
            item.longitude = longitude;
            item.latitude = latitude;
        }
    }

    background: Rectangle {
        anchors.fill: parent
        anchors.centerIn: parent
        color: "transparent"

        Image {
            id: copyIcon

            anchors.centerIn: parent
            source: "../assets/map-regular.svg"
            width: 20
            height: 20
            fillMode: Image.PreserveAspectFit
        }

    }

}
