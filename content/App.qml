// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: mainWindow
    visible: true
    width: 600
    height: 600
    title: "FileExplorer"
    flags: Qt.FramelessWindowHint
    color: "transparent"

    ColumnLayout {
          anchors.fill: parent
          spacing: 0

          Rectangle {
              color: Qt.rgba(0,0,0,0.7)
              Layout.fillWidth: true
              Layout.preferredHeight: 30
              border.color: Qt.rgba(0.549,0.549,0.549,0.6)
              border.width: 1

              Text {
                  color: Qt.rgba(0.2,0.2,1,0.7)
                  text: "<b>qMeta</b>"
                  font.pointSize: 15
                  font.family: ""
                  anchors.verticalCenter: parent.verticalCenter
                  anchors.horizontalCenter: parent.horizontalCenter
              }

              MouseArea {
                  id: dragArea
                  anchors.fill: parent
                  property point clickPos

                  onPressed: function(mouse) {
                      clickPos = Qt.point(mouse.x, mouse.y)
                  }

                  onPositionChanged: function(mouse) {
                      if (mouse.buttons & Qt.LeftButton) {
                          mainWindow.x += mouse.x - clickPos.x
                          mainWindow.y += mouse.y - clickPos.y
                      }
                  }
              }
          }

          Rectangle {
              color: Qt.rgba(0,0,0,0.5)
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
                      color: Qt.rgba(0,0,0,0.3)
                      border.color: Qt.rgba(0.549,0.549,0.549,0.6)
                      border.width: 1

                      ListView {
                          id: fileListView
                          anchors.fill: parent
                          model: fileModel
                          focus: true

                          delegate: Rectangle {
                              width: parent.width
                              height: 30
                              color: ListView.isCurrentItem ? Qt.rgba(0,0,0.6,0.6) : Qt.rgba(0,0,0,0.3)
                              border.color: Qt.rgba(0.549,0.549,0.549,0.6)
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

                        Keys.onPressed: (event) => {
                            if (event.key === Qt.Key_W || event.key === Qt.Key_Up) {
                                if(currentIndex > 0) {
                                    currentIndex--;
                                }
                                event.accepted = true
                            } else if (event.key === Qt.Key_S || event.key === Qt.Key_Down) {
                                if(currentIndex < count - 1) {
                                    currentIndex++;
                                }
                                event.accepted = true
                            } else if (event.key === Qt.Key_Space) {
                                var selectedItem = fileModel.get(fileListView.currentIndex);
                                if (selectedItem) {
                                    fileExplorerController.CR(selectedItem.path);
                                }
                                event.accepted = true;
                            }
                        }
                      }
                  }

                  Rectangle {
                      id: fileViewerPanel
                      Layout.fillHeight: true
                      Layout.fillWidth: true
                      Layout.preferredWidth: 3
                      color: Qt.rgba(0,0,0,0.2)
                      border.color: Qt.rgba(0.549,0.549,0.549,0.6)
                      border.width: 1

                      ListView {
                        id: metadataListView
                        anchors.fill: parent
                        model: ListModel {
                            id: metadataModel
                        }

                        Component.onCompleted: {
                            var metadata = fileModel.getFileMetadata()
                            for (var key in metadata) {
                                metadataModel.append({"key": key,"value": metadata[key]})
                            }
                            console.log("xDDDDD")
                            console.log(JSON.stringify(metadata, null, 4))
                        }

                        delegate: Rectangle {
                            width: parent.width
                            height: 30
                            Row {
                                Text { text: model.key + ": " }
                                Text { text: model.value }
                            }
                        }
                      }
                  }
              }
          }
      }
}

