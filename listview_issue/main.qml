import Qt3D.Core 2.0
import QtQuick.Window 2.2
import QtQuick 2.8
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4 as Qtc1
import QtQuick.Controls 2.1 as Qtc2

import matt 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Blobs {
        id: blobNode
        blobLifeTime: 3500;
    }

    Rectangle {
        Component {
            id: delegate
            Row {
                spacing: 10
                Text { text: "uuid: " + uuid + ", loc = " + centroid.x.toFixed(2); color: "white" }
            }
        }

        RowLayout {
            anchors.fill: parent

            Rectangle {
                Layout.fillHeight: true
                Layout.preferredWidth: 200
                Layout.maximumWidth: 200
                color: "transparent"

                ColumnLayout {
                    anchors.fill: parent

                    Text {
                        text: "Create blob"
                        color: "#e40000"
                    }

                    RowLayout {
                        Text {
                            text: "UUID"
                            color: "#000000"
                            height: 30
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            height: 30;
                            TextEdit {
                                id: uuidEdit
                                text: qsTr("UUID")
                                anchors.horizontalCenterOffset: -46
                                verticalAlignment: Text.AlignVCenter
                                anchors.top: parent.top
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.topMargin: 8
                                Rectangle {
                                    anchors.fill: parent
                                    anchors.margins: -10
                                    color: "transparent"
                                    border.width: 1
                                }
                            }
                       }
                   }
                    RowLayout {
                        Text {
                            text: "Centroid X"
                            color: "#000000"
                            height: 30
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            height: 30;
                            TextEdit {
                                id: xEdit
                                text: qsTr("x")
                                anchors.horizontalCenterOffset: -43
                                verticalAlignment: Text.AlignVCenter
                                anchors.top: parent.top
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.topMargin: 8
                                Rectangle {
                                    anchors.fill: parent
                                    anchors.margins: -10
                                    color: "transparent"
                                    border.width: 1
                                }
                            }
                       }
                   }

                    Qtc2.Button {
                        text: 'Create'
                        onPressed: blobNode.newBlobData(uuidEdit.text, Qt.vector3d(xEdit, 0, 0));
                    }
                }
            }

            Rectangle {
                Layout.fillHeight: true
                Layout.preferredWidth: 200
                Layout.maximumWidth: 200
                color: "transparent"

                ColumnLayout {
                    anchors.fill: parent

                    Text {
                        text: "nBlobs = " + blobNode.blobs.count
                        color: 'white';
                    }

                    Rectangle {

                        Layout.fillWidth: true
                        Layout.minimumWidth: 150
                        Layout.preferredWidth: 180
                        Layout.maximumWidth: 200

                        Layout.minimumHeight: 200
                        Layout.fillHeight: true

                        color: Qt.rgba(0.1, 0.1, 0.3, 0.4)
                        ListView {
                            id: blobsView

                            Layout.fillWidth: true
                            Layout.minimumWidth: 150
                            Layout.preferredWidth: 180
                            Layout.maximumWidth: 200

                            Layout.minimumHeight: 200
                            Layout.fillHeight: true

                            anchors.fill: parent

                            model: blobNode.blobs
                            delegate: delegate
                        }
                    }
                }
            }
        }
    }
}

// vim: ts=3 sw=3 sts=0 noet ffs=unix ft=qml :
