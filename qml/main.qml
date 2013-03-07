/*****************************************************************************
 * main.qml - DictionaryStar, stardict dictionary for MeeGo Harmattan        *
 * Copyright (C) 2012 Jari P.T. Alhonen                                      *
 *                                                                           *
 * This program is free software; you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License as published by      *
 * the Free Software Foundation; either version 3 of the License, or         *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU General Public License for more details.                              *
 *                                                                           *
 * You should have received a copy of the GNU General Public License along   *
 * with this program; if not, see <http://www.gnu.org/licenses/>.            *
 *****************************************************************************/

import QtQuick 1.1
import com.nokia.meego 1.0
 
PageStackWindow {
    id: rootWindow
    initialPage: DictionaryStar { }
    
    Rectangle {
        id: commonTools
        visible: false
        width: parent.width
        height: 64
        anchors.bottom: parent.bottom
        parent: pageStack.currentPage
        z: 1
        
        ToolIcon {
            id: return_img
            iconId: "toolbar-back"
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            MouseArea {
                anchors.fill: parent
                onClicked: pageStack.pop()
                onPressed: return_img.iconId = "toolbar-back-selected"
                onReleased: return_img.iconId = "toolbar-back"
            }
        }
        
        ButtonRow {
            id: moveButtons
            visible: false
            anchors.left: return_img.right
            anchors.right: menuIcon.left
            //anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            platformStyle: ButtonStyle {
                checkedBackground: background
                checkedDisabledBackground: disabledBackground
            }
            Button {
                id: back_img
                enabled: false
                iconSource: "image://theme/icon-m-toolbar-previous"
                onClicked: {
                    pageStack.currentPage.movePage(true)
                    forward_img.enabled = true
                }
            }
            
            Button {
                id: forward_img
                enabled: false
                iconSource: "image://theme/icon-m-toolbar-next"
                onClicked: {
                    pageStack.currentPage.movePage(false)
                    back_img.enabled = true
                }
            }
        }
        
        ToolIcon {
            id: menuIcon
            platformIconId: "toolbar-view-menu"
            anchors.right: (parent === undefined) ? undefined : parent.right
            onClicked: (myMenu.status == DialogStatus.Closed) ? myMenu.open() : myMenu.close()
        }
    } // rectangle commonTools
    
    Menu {
        id: myMenu
        visualParent: pageStack.currentPage
        platformStyle: MenuStyle {
            //background: "" // PR1.0 doesn't support setting the background!
            bottomPadding: commonTools.height
        }
        
        function openPage(url) {
            if(pageStack.depth > 2) {
                pageStack.replace(Qt.resolvedUrl("DictWebView.qml"), {
                    loadUrl: url
                });
            } else {
                pageStack.push(Qt.resolvedUrl("DictWebView.qml"), {
                    loadUrl: url
                });
            }
        }
        
        MenuLayout {
            MenuItem {
                text: qsTr("Adding Dictionaries")
                platformStyle: MenuItemStyle {
                    fontPixelSize: 32
                    fontWeight: Font.Bold
                }
                onClicked: {
                    if(pageStack.depth > 2) {
                        pageStack.pop()
                        pageStack.currentPage.moveToFooter()
                    } else {
                        pageStack.currentPage.moveToFooter()
                    }
                }
            }
            MenuItem {
                text: "-> abloz.com"
                platformStyle: MenuItemStyle {
                    fontWeight: Font.Normal
                    leftMargin: 150
                }
                onClicked: myMenu.openPage("http://abloz.com/huzheng/stardict-dic/")
            }
            MenuItem {
                text: "-> sourceforge.net"
                platformStyle: MenuItemStyle {
                    fontWeight: Font.Normal
                    leftMargin: 150
                }
                onClicked: myMenu.openPage("http://sourceforge.net/projects/xdxf/files/dicts-stardict-form-xdxf/")
            }
        }
    } // menu
}
