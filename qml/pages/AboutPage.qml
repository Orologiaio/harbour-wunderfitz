/*
  (c) 2016 by Sebastian J. Wolf
  www.wunderfitz.org
*/

import QtQuick 2.0
import Sailfish.Silica 1.0


Page {
    id: aboutPage

    SilicaFlickable {
        id: aboutContainer
        contentHeight: column.height
        anchors.fill: parent

        Column {
            id: column
            width: aboutPage.width
            spacing: Theme.paddingLarge

            PageHeader {
                title: qsTr("About Wunderfitz")
            }

            Image {
                id: wunderfitzImage
                source: "../images/wunderfitz.png"
                anchors {
                    horizontalCenter: parent.horizontalCenter
                }

                fillMode: Image.PreserveAspectFit
                width: 1/2 * parent.width

            }

            Label {
                text: qsTr("Wunderfitz 0.1")
                font.pixelSize: Theme.fontSizeExtraLarge
                anchors {
                    horizontalCenter: parent.horizontalCenter
                }
            }

            Label {
                text: qsTr("A Norwegian-German dictionary")
                font.pixelSize: Theme.fontSizeSmall
                anchors {
                    horizontalCenter: parent.horizontalCenter
                }
            }

            Label {
                text: qsTr("By Sebastian J. Wolf")
                font.pixelSize: Theme.fontSizeSmall
                anchors {
                    horizontalCenter: parent.horizontalCenter
                }
            }

            SectionHeader {
                text: qsTr("Additional information")
            }

            Label {
                text: qsTr("Licensed under GNU GPLv2")
                font.pixelSize: Theme.fontSizeSmall
                anchors {
                    horizontalCenter: parent.horizontalCenter
                }
            }

            Button {
                text: qsTr("Project Page")
                anchors {
                    horizontalCenter: parent.horizontalCenter
                }
                onClicked: Qt.openUrlExternally("http://www.wunderfitz.info/")
            }

            SectionHeader {
                text: qsTr("Credits")
            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*x
                text: qsTr("This project uses data from heinzelnisse.info. Thanks to the authors Heiko Klein and Julia Emmerich for making the dictionary accessible under the conditions of the GNU GPLv2!")
                font.pixelSize: Theme.fontSizeExtraSmall
                wrapMode: Text.Wrap
                anchors {
                    horizontalCenter: parent.horizontalCenter
                }
            }

            Button {
                text: qsTr("Heinzelnisse")
                anchors {
                    horizontalCenter: parent.horizontalCenter
                }
                onClicked: Qt.openUrlExternally("http://www.heinzelnisse.info/")
            }
            VerticalScrollDecorator {}
        }

    }
}





