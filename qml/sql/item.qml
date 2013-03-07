import QtQuick 1.1
import com.nokia.meego 1.1

Rectangle {
    anchors.fill: parent
    property variant message;

    Component {
        id: dictDelegate

        Rectangle {
            width: parent.width
            height: wordLabel.height+ seperator.height+detailLabel.height
            Text {
                id: wordLabel
                text: name
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 30
                color: "red"
            }

            CheckBox {
                id: checkBox
                anchors.verticalCenter: wordLabel.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10

                checked: false
                onClicked: {}
            }

            Rectangle {
                id: seperator
                anchors.top: wordLabel.bottom
                width: parent.width -18
                x: 5
                height: 2
                color: "lightgrey"
            }


            Text {
                id: detailLabel
                //anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: seperator.bottom
                text: content
                width: parent.width
                wrapMode: Text.WordWrap
                //horizontalAlignment: Text.AlignHCenter
                //verticalAlignment: Text.AlignVCenter
                font.pointSize: 20
                color: "blue"
                opacity: 1
            }

            /*
    ToolIcon {
        id: check
        anchors.left: wordLabel.right
        anchors.verticalCenter: wordLabel.verticalCenter

        property string image1:"invitation-accept"
        property string image2:"invitation-declined"
        iconId: image1
        state: ''
        onClicked: {
            if(state =='') state = "checked"
            else state = ''
        }
        states:
        State{
            name: "checked"
            PropertyChanges{target: check; iconId: image2 }
        }
    }
    */

        }
    }

    ListView {
        id: mainView
        width: parent.width
        anchors.top: parent.top
        anchors.bottom: toolBar.top
        model: dictCore.table
        orientation: Flickable.VerticalFlick
        snapMode: ListView.NoSnap
        delegate: dictDelegate
        spacing: 6

    }

    ScrollDecorator {
        flickableItem: mainView
    }
    ToolBar {
        id: toolBar
        anchors.bottom: parent.bottom
        tools: ToolBarLayout {
            ToolIcon { iconId: "toolbar-back"; onClicked: { pageStack.pop(); }  }
            ToolIcon { iconId: "toolbar-view-menu"; onClicked: { }  }
        }
    }


}
