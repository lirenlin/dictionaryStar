// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.1
import com.nokia.extras 1.1
//import com.lirenlin.qmlviewer 1.0
// store some global variable



Page {
    id: wordbook
    property string currentWord
    orientationLock: PageOrientation.LockPortrait
    //width: screenWidth
    //height: screenHeight
    anchors.centerIn: parent

    /*
     function openFile(file) {
         var component = Qt.createComponent(file);
         pageStack.push(component);
     }
     */

    Component {
        id: wordDelegate
        Rectangle {
            id: wordCard
            height: 60
            width: listView.width

                Text {
                    id: wordLabel
                    //width: parent.width
                    text: name
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    font.pointSize: 20
                    horizontalAlignment: Text.AlignLeft
                }
                Text {
                    id: detailLabel
                    //width: parent.width
                    text: date 
                    anchors.top: wordLabel.bottom
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    font.pointSize: 16
                    font.weight: Font.Light
                    horizontalAlignment: Text.AlignLeft
                    opacity: 0.6
                    visible: true
                }
                ToolIcon { 
                    iconId: "toolbar-next"
                    z: parent.z + 1
                    opacity: 0.6
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        listView.currentIndex = index
                        pageStack.push(Qt.resolvedUrl("item.qml"), {wordName:name})
                    }
                }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
		hoverEnabled: true

                Menu {
                    id: contextMenu
                    content: MenuLayout {
                        MenuItem {
                            text: "Delete"
                            onClicked: {
                                db.removeRow(name)
                                print(index);
                                listModel.remove(index);
                                //listModel.loadDB();
                            }
                        }
                    }
                }
/*
                onClicked: {
                    //var info = {"wordName":name, "wordDetail":mean}
                    pageStack.push(Qt.resolvedUrl("item.qml"), {wordName:name})
                }
*/
                onPressAndHold: contextMenu.open()
                onPressed: { listView.currentIndex = index}

            ListView.onRemove: SequentialAnimation {
                PropertyAction { target: wordCard; property: "ListView.delayRemove"; value: true }
                NumberAnimation { target: wordCard; property: "height"; to: 0; duration: 250; easing.type: Easing.InOutQuad }

                // Make sure delayRemove is set back to false so that the item can be destroyed
                PropertyAction { target: wordCard; property: "ListView.delayRemove"; value: false }
            }
            }
        }
    }



    Rectangle {
        id: headerBar
        anchors.top: parent.top
        width: parent.width
        z: parent.z + 1
        height: 60
        Rectangle {
            id: rectangle
            anchors.fill: parent
            //  radius: 10
            color: "#00599b"
            Text {
                text: "Word Book"
                color: "white"
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignLeft
                font.pointSize: 30
            }

        }
        Image {
            anchors { bottom: rectangle.bottom; left: rectangle.left; right: rectangle.right}
            anchors { bottomMargin: -10 }
            source: "image://theme/meegotouch-menu-shadow-bottom"
        }
    }
    ListView {
        id: listView
        //width: parent.width
        anchors.top: headerBar.bottom
        anchors.bottom: toolBar.top
        anchors.left: parent.left
        anchors.right: parent.right
        clip: true
        //anchors.fill: parent

        spacing: 2
        model: listModel
        delegate: wordDelegate
        preferredHighlightBegin: 0; preferredHighlightEnd: 0
        //highlightRangeMode: ListView.StrictlyEnforceRange
        orientation: ListView.Vertical
        //snapMode: ListView.SnapToItem;
        flickDeceleration: 2000
	cacheBuffer: 1200
	highlightFollowsCurrentItem: false
	highlight: Rectangle {
		width: parent.width; height: 60
	        color: "#FFFF88"
		opacity: 0.4
		z: listView.currentItem.z+1
	        y: listView.currentItem.y;
	        Behavior on y { SpringAnimation { spring: 2; damping: 0.1 } }
		}
    }

    ScrollDecorator {
        flickableItem: listView
    }

    ToolBar {
        id: toolBar
        anchors.bottom: parent.bottom
        tools: ToolBarLayout {
            ToolIcon {
                iconId: "toolbar-back";
                onClicked:{
                    dictCore.translate(currentWord);
                    pageStack.pop();
                } 
            }
            //ToolButton { visible: false}
            //ToolButton {iconSource: "image://theme/icon-m-toolbar-back"; flat: true}
            ToolIcon {
                iconId: "toolbar-view-menu";
                onClicked: { mainMenu.open() }
            }
        }
    }

    Menu {
        id: mainMenu
        content: MenuLayout {
            /*
            MenuItem {
                text: "context menu"
                onClicked: {
                    dialog1.open()
                    db.addRow("who", "this", "that")
                }
            } */
            MenuItem {
                text: "start"
                onClicked: {
                    //pageStack.push(Global.reviewPage, { listModel: listModel});
                    pageStack.push(Qt.resolvedUrl("reviewpage.qml"))

                }
            }
        }
    }

    /*
    SelectionDialog {
        id: dialog1
        titleText: "Select team:"
        model: ListModel {
            ListElement { name: "Rock" }
            ListElement { name: "Paper" }
            ListElement { name: "Scissors" }
        }
    }
    */

    //Component.onCompleted: db.addRow("this", "that", "hallo")
    //Component.onCompleted: qmlviewer.setOrientation(QMLViewer.ScreenOrientationLockPortrait);

}
