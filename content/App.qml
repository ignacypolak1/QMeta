// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: mainWindow

    visible: true
    width: 1200
    height: 600
    title: "FileExplorer"
    flags: Qt.FramelessWindowHint
    color: "transparent"

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            color: Qt.rgba(0, 0, 0, 0.7)
            Layout.fillWidth: true
            Layout.preferredHeight: 30
            border.color: Qt.rgba(0.549, 0.549, 0.549, 0.6)
            border.width: 1

            MouseArea {
                id: dragArea

                property point clickPos

                anchors.fill: parent
                onPressed: function(mouse) {
                    clickPos = Qt.point(mouse.x, mouse.y);
                }
                onPositionChanged: function(mouse) {
                    if (mouse.buttons & Qt.LeftButton) {
                        mainWindow.x += mouse.x - clickPos.x;
                        mainWindow.y += mouse.y - clickPos.y;
                    }
                }
            }

        }

        Rectangle {
            color: Qt.rgba(0, 0, 0, 0.5)
            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout {
                anchors.fill: parent
                spacing: 0

                Rectangle {
                    id: fileSelectionPanel

                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 2
                    color: Qt.rgba(0, 0, 0, 0.3)
                    border.color: Qt.rgba(0.549, 0.549, 0.549, 0.6)
                    border.width: 1

                    ListView {
                        id: fileListView

                        anchors.fill: parent
                        model: fileModel
                        focus: true
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

                Rectangle {
                    id: fileViewerPanel

                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 3
                    color: Qt.rgba(0, 0, 0, 0.2)
                    border.color: Qt.rgba(0.549, 0.549, 0.549, 0.6)
                    border.width: 1

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
                                    width: parent.width / 2
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
                                    width: parent.width / 2
                                    height: parent.height
                                    border.color: "grey"
                                    border.width: 1
                                    color: "transparent"

                                    Text {
                                        text: value
                                        anchors.centerIn: parent
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        color: "white"
                                    }

                                }

                            }

                        }

                    }

                }

            }

        }

    }

}
