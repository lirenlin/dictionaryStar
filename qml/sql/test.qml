// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.1
import com.nokia.extras 1.1
//import com.lirenlin.qmlviewer 1.0
// store some global variable
import "variable.js" as Global

PageStackWindow {
    id: rootWindow


    initialPage: Page {
        id: mainPage
        orientationLock: PageOrientation.LockPortrait
        anchors.centerIn: parent

        Component {
            id: wordDelegate
            Rectangle {
                id: wordCard
                height: 80
                width: listView.width

                Row {
                Text {
                    id: wordLabel
                    //width: parent.width
                    text: ID + ' ' + name
                    font.bold: true; font.pointSize: 16
                    horizontalAlignment: Text.AlignLeft
                }
                Text {
                    id: detailLabel
                    //width: parent.width
                    text: ': ' + mean
                    font.bold: true; font.pointSize: 16
                    //horizontalAlignment: Text.AlignLeft
                    visible: true
                }
                }
            }
        }



        ListView {
            id: listView
            //width: parent.width
            anchors.top: parent.top
            anchors.bottom: toolBar.top
            anchors.left: parent.left
            anchors.right: parent.right
            clip: true
            //anchors.fill: parent

            spacing: 2
            model: listModel
            delegate: wordDelegate
            preferredHighlightBegin: 0; preferredHighlightEnd: 0
            orientation: ListView.Vertical
            snapMode: ListView.SnapToItem;
            //flickDeceleration: 2000

            /*
            Component.onCompleted: {
                print(listView.contentHeight)
                var height = 0;
                for(var i = 0; i < count; ++i)
                    height += 80 + spacing;
                contentHeight = height
                print(height)
                print(listView.contentHeight)
            }
            */

onContentHeightChanged: { console.log(contentHeight) }

        }
    ScrollDecorator {
        flickableItem: listView
    }

        ToolBar {
            id: toolBar
            anchors.bottom: parent.bottom
            tools: ToolBarLayout {
                //ToolIcon { iconId: "toolbar-back"; onClicked: { Qt.quit(); }  }
                //ToolButton { visible: false}
                //ToolButton {iconSource: "image://theme/icon-m-toolbar-back"; flat: true}
                ToolIcon {
                    iconId: "toolbar-view-menu";
                    onClicked: { mainMenu.open() }
                }
            }
        }

        //Component.onCompleted: qmlviewer.setOrientation(QMLViewer.ScreenOrientationLockPortrait);

    }
}
