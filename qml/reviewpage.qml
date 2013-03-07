// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.1
import com.nokia.extras 1.0
//import com.lirenlin.qmlviewer 1.0

 Page {
     id: reviewPage
     orientationLock: PageOrientation.LockLandscape
     anchors.centerIn: parent

    property int period:4

    /*
    Rectangle {
        anchors.fill: parent
        opacity: 0.8
        gradient: Gradient {
            GradientStop { position:0.0; color: "lightblue" }
            GradientStop { position:1.0; color: "transparent" }
        }
    }
    */


        Component {
        id: review
        Rectangle {
            id: wordCard
            width: view.width
            height: view.height
            border.width: 10
            border.color: "lightblue"
            color: "transparent"

            Text {
                id: wordLabel
                text: name
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 30
                color: "red"
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: detailLabel.toggle()

            }
            }
            Flickable {
                id: flickable
                width: parent.width
                anchors.top: wordLabel.bottom
                anchors.bottom: parent.bottom
                contentHeight: detailLabel.height
                flickableDirection: Flickable.VerticalFlick
                clip: true
                Text {
                    id: detailLabel
                    //anchors.horizontalCenter: parent.horizontalCenter
                    //anchors.top: wordLabel.bottom
                    text: mean
                    width: parent.width
                    wrapMode: Text.WordWrap
                    horizontalAlignment: Text.AlignHCenter
                    //verticalAlignment: Text.AlignVCenter
                    font.pointSize: 20
                    color: "blue"
                    opacity: 0
                    PropertyAnimation {
                        id: toggleAnimate;
                        target: detailLabel;
                        to: 1
                        property: "opacity";
                        duration: 500
                    }

                    function toggle()
                    {
                        var opacity = 0;
                        if(detailLabel.opacity == 0) opacity = 1

                        toggleAnimate.to = opacity;
                        toggleAnimate.running = true;
                    }
                }
            }
            ScrollDecorator {
                flickableItem: flickable
            }

        }
    }

    ListView {
        id: view
        width: parent.width
        //height: parent.height
        anchors.top: parent.top
        anchors.bottom: toolBar.top
        spacing: 10

        model: listModel
        delegate: review
        preferredHighlightBegin: 0; preferredHighlightEnd: 0
        highlightRangeMode: ListView.StrictlyEnforceRange

        orientation: ListView.Horizontal
        snapMode: ListView.SnapOneItem;
        maximumFlickVelocity: 50

        //flickDeceleration: 10
        //cacheBuffer: 100
        highlightMoveSpeed: 1000
    }

	InfoBanner {
		id: sb
		text: "Reach the list end!"
		timerShowTime: 2000
		}
    Timer {
        id: timer
        interval: reviewPage.period*1000; repeat: true
	signal end();
        onTriggered: {
            if(view.currentIndex == view.count -1) {
                stop();
		end();
		sb.show();
            }
            else view.incrementCurrentIndex()
        }
    }

    ToolBar {
        id: toolBar
        anchors.bottom: parent.bottom
        tools: ToolBarLayout {
            ToolIcon { iconId: "toolbar-back"; onClicked: { pageStack.pop(); }  }
            ToolIcon {
                iconId: "toolbar-mediacontrol-play";
                onClicked: {
                    if( timer.running) {
                        iconId = "toolbar-mediacontrol-play"
                        timer.running = false
                    }
                    else {
                        timer.running = true
                        iconId = "toolbar-mediacontrol-pause"
                    }
                }
		function end() {  iconId = "toolbar-mediacontrol-play" }
                Component.onCompleted: timer.end.connect(end);
            }
            ToolIcon { iconId: "toolbar-view-menu"; onClicked: mainMenu.open()  }
        }
    }
        Menu {
            id: mainMenu
            content: MenuLayout {
                MenuItem {
                    text: "timer"
                    onClicked: timePicker.open()
                }
            }
        }
        // may add default value
        TimePickerDialog {
            id: timePicker
            titleText: "timer period"
            //fields: DateTime.Minutes | DateTime.Seconds
            fields: DateTime.Seconds
            hourMode: DateTime.TwentyFourHours
            acceptButtonText: "OK"
            rejectButtonText: "Cancel"

            signal sure;
            property int period: 4
            second: period

            onAccepted: {
                period =  second;
                if(period <= 4 )
                    queryDialog.open()
                else
                    reviewPage.period = period;
            }

            onSure: reviewPage.period =  period

            QueryDialog {
                id: queryDialog
                icon: "image://theme/icon-m-common-fault"
                titleText: "Warning"
                message: "Are you sure? It's too fast!!"
                acceptButtonText: "Accept"
                rejectButtonText: "Reject"
                onAccepted: timePicker.sure()
                onRejected: timePicker.open()
            }
        }
        //Component.onCompleted: qmlviewer.setOrientation(QMLViewer.ScreenOrientationLockLandscape);

 }
