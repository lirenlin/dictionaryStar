// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.1

Page {
    id: newPagewithLabel
    property variant message;


    // load meaning from dictionaries
    function loadFromDict(name)
    {

    }
    Text {
        id: wordLabel
        text: message.wordName
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 30
        color: "red"
    }

    CheckBox {
        id: checkBox
        anchors.verticalCenter: wordLabel.verticalCenter
        anchors.left: wordLabel.right
        anchors.leftMargin: 20

        checked: false
        onClicked: {}
    }

    Rectangle {
        id: seperator
        anchors.top: wordLabel.bottom
        width: parent.width -10
        x: 5
        height: 2
        color: "lightgrey"
    }

    Flickable {
        id: flickable
        width: parent.width
        anchors.top: seperator.bottom
        anchors.bottom: toolBar.top
        contentHeight: detailLabel.height
        flickableDirection: Flickable.VerticalFlick
    Text {
        id: detailLabel
        width: parent.width
        //text: message.wordDetail
        text: "so many text\nso many text\nso many text\nso many textso many textso many textso many textso many textso many textso many textso many textso many text"
        wrapMode: Text.WordWrap
        font.pointSize: 18
        color: "red"
    }
    }
    ScrollDecorator {
        flickableItem: flickable
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
