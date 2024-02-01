import QtLocation 6.7
import QtPositioning 6.7
import QtQuick 2.12
import QtQuick.Controls 2.12

Window {
    property double latitude
    property double longitude

    visible: true
    width: 800
    height: 600
    title: "Coordinates"

    Map {
        id: map

        anchors.fill: parent
        center: QtPositioning.coordinate(latitude, longitude)

        DragHandler {
            id: drag

            target: null
            onTranslationChanged: (delta) => {
                return map.pan(-delta.x, -delta.y);
            }
        }

        MouseArea {
            anchors.fill: parent
            onWheel: {
                var scale = 0.5;
                if (wheel.angleDelta.y > 0)
                    map.zoomLevel = Math.min(map.zoomLevel + scale, map.maximumZoomLevel);
                else
                    map.zoomLevel = Math.max(map.zoomLevel - scale, map.minimumZoomLevel);
            }
        }

        MapQuickItem {
            coordinate: QtPositioning.coordinate(latitude, longitude)
            anchorPoint: Qt.point(10, 10)

            sourceItem: Rectangle {
                width: 20
                height: 20
                color: "red"
                border.color: "white"
                radius: 10
            }

        }

        plugin: Plugin {
            id: osmPlugin

            name: "osm"

            PluginParameter {
                name: "osm.mapping.custom.host"
                value: "https://tile.thunderforest.com/cycle/{z}/{x}/{y}.png?apikey=2b6040f28ea146799f74820885e95"
            }

        }

    }

}
