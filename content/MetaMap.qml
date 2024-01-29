import QtLocation 6.6
import QtPositioning
import QtQuick 2.12
import QtQuick.Controls 2.12

Window {
    property double latitude: 53.4285
    property double longitude: 14.5528

    visible: true
    width: 800
    height: 600
    title: "Coordinates"

    Map {
        id: map

        anchors.fill: parent
        center: QtPositioning.coordinate(latitude, longitude)

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
