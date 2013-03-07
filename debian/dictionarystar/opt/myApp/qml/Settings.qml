/*******************************************************************************
 * Settings.qml - DictionaryStar, stardict dictionary for MeeGo Harmattan      *
 * Copyright (C) 2012 Jari P.T. Alhonen                                        *
 *                                                                             *
 * This program is free software; you can redistribute it and/or modify        *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation; either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License along     *
 * with this program; if not, see <http://www.gnu.org/licenses/>.              *
 *******************************************************************************/

import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: settingPage
    property bool delayedMoveToFooter: false
    
    function openDownloadView(url) {
        pageStack.push(Qt.resolvedUrl("DictWebView.qml"), {
            loadUrl: url
        });
    }
    
    function moveToFooter() {
        if(status != PageStatus.Active)
            delayedMoveToFooter = true
        else {
            dictList.positionViewAtIndex(dictList.count - 1, ListView.Beginning)
            // unfortunately there is no function to position at the beginning of the footer
            dictList.contentY += 45 // 45 is the height of an item -- item id doesn't work here
        }
    }
    
    onStatusChanged: {
        if(status == PageStatus.Active) {
            return_img.visible = !dictCore.noEnabledDictionaries()
            dictCore.updateModel()
            commonTools.visible = true
            moveButtons.visible = false
            if(delayedMoveToFooter) {
                moveToFooter()
                delayedMoveToFooter = false
            }
        }
    }
    
    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height - commonTools.height
        
        PinchArea {
            anchors.fill: parent
            onPinchUpdated: {
                var desiredSize = pinch.scale * dictList.currentFontSize
                if(desiredSize >= dictList.minimumFontSize && desiredSize <= dictList.maximumFontSize)
                    dictList.fontSize = desiredSize
            }
            onPinchFinished: {
                var desiredSize = pinch.scale * dictList.currentFontSize
                if(desiredSize >= dictList.minimumFontSize && desiredSize <= dictList.maximumFontSize)
                    dictList.fontSize = desiredSize
                    dictList.currentFontSize = dictList.fontSize
                    dictCore.setDefaultFontSize(dictList.currentFontSize)
            }
        }
        
        Component {
            id: header
            
            Rectangle {
                width: settingPage.width
                height: headline.height
                Text {
                    id: headline
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: dictList.fontSize
                    text: "<h2>"+qsTr("Available Dictionaries")+"</h2>"
                    visible: dictList.count > 0
                }
            }
        }
        
        ListView {
            id: dictList
            anchors.fill: parent
            clip: true
            property int currentFontSize: dictCore.defaultFontSize()
            property int fontSize: dictCore.defaultFontSize()
            property int minimumFontSize: 10
            property int maximumFontSize: 60
            height: parent.height
            
            header: header
            model: dictsModel
            footer: footer
            
            delegate: Rectangle {
                id: dictItem
                height: 45
                anchors.right: parent.right
                anchors.left: parent.left
                
                CheckBox {
                    id: dictEnable
                    checked: useDict
                    onClicked: {
                        dictCore.enableDictionary(name, plugin, checked)
                        return_img.visible = !dictCore.noEnabledDictionaries()
                    }
                }
                
                Text {
                    id: dictName;
                    text: name
                    anchors.left: dictEnable.right
                    font.pixelSize: dictList.fontSize
                    anchors.verticalCenter: dictEnable.verticalCenter
                }
                Text {
                    id: pluginName
                    anchors.left: dictName.right
                    anchors.leftMargin: 10
                    font.pixelSize: dictList.fontSize / 2
                    font.italic: true
                    text: plugin
                    anchors.verticalCenter: dictEnable.verticalCenter
                }
                
                MouseArea {
                    id: dragArea
                    anchors.left: dictName.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    property int positionStarted: 0
                    property int positionEnded: 0
                    property int positionsMoved: ((positionEnded - positionStarted)/parent.height)
                    property int newPosition: index + positionsMoved
                    property bool held: false
                    drag.axis: Drag.YAxis
                    onPressAndHold: {
                        if(dictEnable.checked) {
                            dictItem.z = 2
                            dictItem.opacity = 0.5
                            dictList.interactive = false
                            positionStarted = dictItem.y
                            dragArea.drag.target = dictItem
                            held = true
                            drag.maximumY = (dictList.height - parent.height - 1 + dictList.contentY)
                            drag.minimumY = 0
                        } else {
                            deleteDialog.dictName = dictName.text
                            deleteDialog.pluginName = pluginName.text
                            deleteDialog.open()
                        }
                    }
                    onReleased: {
                        positionEnded = dictItem.y;
                        if (Math.abs(positionsMoved) < 1 && held == true) {
                            dictItem.y = positionStarted
                            dictItem.opacity = 1
                            dictList.interactive = true
                            dragArea.drag.target = null
                            held = false
                        } else {
                            if (held == true) {
                                if (newPosition < 1) {
                                    dictItem.z = 1
                                    dictCore.moveItem(index, 0)
                                    dictList.interactive = true
                                    dragArea.drag.target = null
                                    held = false
                                } else if (newPosition > dictList.count - 1) {
                                    dictItem.z = 1
                                    dictCore.moveItem(index, dictList.count -1)
                                    dictItem.opacity = 1
                                    dictList.interactive = true
                                    dragArea.drag.target = null
                                    held = false
                                } else {
                                    dictItem.z = 1
                                    dictCore.moveItem(index, newPosition)
                                    dictItem.opacity = 1
                                    dictList.interactive = true
                                    dragArea.drag.target = null
                                    held = false
                                }
                            }
                        }
                    } // onReleased
                } // dragArea
            } // delegate
        } // listview

        ScrollDecorator {
            flickableItem: dictList
        }
        
        Component {
            id: footer
            
            Rectangle {
                width: settingPage.width
                height: info_header.height + info.height + download.height + import_dict.height + 30
                
                Text {
                    id: info_header
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: dictList.fontSize
                    text: "<h2>"+qsTr("Adding Dictionaries")+"</h2>"
                }
                
                Text {
                    id: info
                    anchors.top: info_header.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 65
                    anchors.leftMargin: 20
                    anchors.topMargin: 10
                    width: parent.width
                    font.pixelSize: dictList.fontSize
                    wrapMode: Text.Wrap
                    text: "<p>"+qsTr("Dictionary files in StarDict format for various languages are available for free online.")+"</p>"
                }
                
                Text {
                    id: download
                    anchors.top: info.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 130
                    anchors.leftMargin: 20
                    anchors.topMargin: 10
                    width: parent.width
                    font.pixelSize: dictList.fontSize
                    wrapMode: Text.Wrap
                    text: "<p>"+qsTr("Dictionaries downloaded with the built-in browser will be automatically installed. Just click links: ")
                    +" <a href=\"http://abloz.com/huzheng/stardict-dic/\">abloz.com</a> " + qsTr("or")
                    +" <a href=\"http://sourceforge.net/projects/xdxf/files/dicts-stardict-form-xdxf/\">sourceforge.net</a>.</p>"
                    onLinkActivated: settingPage.openDownloadView(link)
                }
                
                Image {
                    id: download_img
                    width: 64
                    height: 64
                    source: "qrc:/images/download.png"
                    anchors.right: parent.right
                    anchors.rightMargin: 65
                    anchors.verticalCenter: download.verticalCenter
                    MouseArea {
                        anchors.fill: parent
                        onClicked: settingPage.openDownloadView("http://abloz.com/huzheng/stardict-dic/")
                    }
                }
                
                Text {
                    id: import_dict
                    anchors.top: download.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 65
                    anchors.leftMargin: 20
                    anchors.topMargin: 10
                    width: parent.width
                    font.pixelSize: dictList.fontSize
                    wrapMode: Text.Wrap
                    text: "<p>"+qsTr("Alternatively, you can download dictionaries manually from the regular browser or copy them from a PC. To install in this method, copy the extracted dictionaries to")
                    +" <code>/home/user/.stardict/dic/</code></p><p><small>"
                    +qsTr("This program is free software under ")+"<a href=\"http://www.gnu.org/copyleft/gpl.html\">"+qsTr("GPL license")+"</a>"
                    +qsTr(". The source code can be downloaded from")+" <a href=\"https://gitorious.org/dictionarystar/pages/Home\">gitorious.org/dictionarystar</a>.</small></p>"
                    onLinkActivated: Qt.openUrlExternally(link)
                }
            } // rectangle
        } // component
    } // whole page rectangle
    
    QueryDialog {
        id: deleteDialog
        property string dictName
        property string pluginName
        property string promptPreamble: qsTr("Delete ")
        property string promptMidamble: qsTr(" dictionary ")
        property string promptPostamble: qsTr("?")
        property string promptNote: qsTr("This operation cannot be undone.")
        icon: "qrc:/images/trash.png"
        acceptButtonText: qsTr("Yes")
        rejectButtonText: qsTr("No")
        titleText: qsTr("Delete Dictionary")
        message: promptPreamble + pluginName + promptMidamble + dictName + promptPostamble + promptNote
        onAccepted: {
            dictCore.deleteDictionary(pluginName, dictName)
//             headline.visible = dictList.count > 0
            commonTools.visible = true
        }
        onRejected: commonTools.visible = true
        onStatusChanged: {
            if(status == DialogStatus.Opening) {
                commonTools.visible = false
                message = "<p>" + promptPreamble + pluginName + promptMidamble + "\"" + dictName + "\"" + promptPostamble + "</p><p>" + promptNote + "</p>"
            }
        }
    }
} // page
