import QtQuick 2.6
import Sailfish.Silica 1.0

import QtPositioning 5.3
import QtLocation 5.0
import "../assets"

Page {

    property real latitude: positionSource.position.coordinate.latitude
    property real longitude: positionSource.position.coordinate.longitude

    // Для позиционирования либо использовать nmea,
    // либо задать координаты через "Инструменты -> AuroraOs -> Управление эмуляцией -> Местоположение"
    PositionSource {
        id: positionSource
        active: true
        nmeaSource: "../../nmea/path.nmea"
    }

    Map {
        id: map
        anchors.fill: parent
        gesture.enabled: true
        zoomLevel: zoomSlider.value

        plugin: Plugin {
            id: mapPlugin
            objectName: "mapPlugin"
            name: "webtiles"
            allowExperimental: false

            PluginParameter {
                name: "webtiles.scheme"
                value: "https"
            }
            PluginParameter {
                name: "webtiles.host"
                value: "tile.openstreetmap.org"
            }
            PluginParameter {
                name: "webtiles.path"
                value: "/${z}/${x}/${y}.png"
            }
        }

        Component.onCompleted: center = QtPositioning.coordinate(56.85836,
                                                                 35.90057)
    }

    Binding {
        target: map
        property: "center"
        value: positionSource.position.coordinate
        when: positionSource.position.coordinate.isValid
    }

    Label {
        text: qsTr("Широта: %1,\nДолгота: %2").arg(latitude).arg(longitude)
        color: "black"
        anchors {
            left: parent.left
            top: parent.top
            topMargin: Theme.paddingMedium
            leftMargin: Theme.paddingMedium
        }
    }

    Slider {
        id: zoomSlider
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            bottomMargin: Theme.paddingLarge
        }
        color: "black"
        highlightColor: "black"
        minimumValue: map.minimumZoomLevel
        maximumValue: map.maximumZoomLevel
        value: 11
    }

    Footprints {
        id: footprints
        coordinate: positionSource.position.coordinate
        visible: positionSource.position.coordinate.isValid
        diameter: Math.min(map.width, map.height) / 8
    }

    Component.onCompleted: {
        map.addMapItem(footprints)
    }
}
