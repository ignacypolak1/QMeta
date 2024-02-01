// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import Qt.labs.platform
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

                FileSelectionPanel {
                    id: fileSelectionPanel
                }

                MetaViewPanel {
                    id: metaViewPanel
                }

            }

        }

    }

}
