/*******************************************************************************
 * DictWebView.qml - DictionaryStar, stardict dictionary for MeeGo Harmattan   *
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
import DictWebLib 1.0
import com.nokia.meego 1.0

Page {
    id: downloadPage
    property string loadUrl

    onStatusChanged: {
        if(status == PageStatus.Active) {
            return_img.visible = true
            moveButtons.visible = true
        }
    }
    
    function movePage(direction) {
        downloadView.movePage(direction)
        dictDownload.returnToBounds()
    }
    
    Flickable {
        id: dictDownload
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height - commonTools.height
        flickableDirection: Flickable.HorizontalAndVerticalFlick
        contentHeight: downloadView.height
        contentWidth: downloadView.width
        
        PinchArea {
            anchors.fill: parent
            onPinchUpdated: downloadView.zoomFactor = pinch.scale * downloadView.currentScale
            onPinchFinished: {
                downloadView.zoomFactor = pinch.scale * downloadView.currentScale
                downloadView.currentScale = downloadView.zoomFactor
                if(pinch.scale < 1.0) {
                    downloadView.height *= pinch.scale
                    downloadView.width *= pinch.scale
                    dictDownload.returnToBounds()
                }
            }
        }
        
        DictWebView {
            id: downloadView
            property real preferredHeight
            property real preferredWidth
            property real currentScale: 1.0
            signal completedImport(string dicts)
            signal failedImport()
            url: downloadPage.loadUrl
            
            onContentSizeChanged: {
                height = contentHeight
                width = contentWidth
            }
            
            onImportCompleted: {
                if(dicts == "")
                    failedImport()
                    else
                        completedImport(dicts)
            }
            width: parent.width
            height: parent.height
            preferredHeight: parent.height
            preferredWidth: parent.width
            
            onCompletedImport: {
                downloadProgress.visible = false
                dictCore.enableDictionaries(dicts)
                successReport.text = successReport.success
                successReport.opacity = 1
            }
            
            onFailedImport: {
                downloadProgress.visible = false
                successReport.text = successReport.failure
                successReport.opacity = 1
            }
            
            onDownloadProgress: {
                downloadProgress.maximumValue = total
                downloadProgress.value = current
                downloadProgress.visible = true
            }
            
            onLinkClicked: {
                busy.visible = true
                back_img.enabled = true
                forward_img.enabled = false
            }
            
            onLoadFinished: busy.visible = false
            
            onHideButton: {
                if(back)
                    back_img.enabled = false
                else
                    forward_img.enabled = false
            }
        }
    }
    
    ScrollDecorator {
        flickableItem: dictDownload
    }
    
    ProgressBar {
        id: downloadProgress
        width: parent.width / 2
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        minimumValue: 0
        visible: false
    }
    
    Text {
        id: successReport
        property string failure: "<b><font color=\"red\">"+qsTr("Dictionary import failed.")+"</font></b>"
        property string success: "<b><font color=\"green\">"+qsTr("Dictionary successfully imported.")+"</font></b>"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 25
        opacity: 0
        onOpacityChanged: PropertyAnimation { target: successReport; property: "opacity"; to: 0; duration: 2000 }
    }
    
    BusyIndicator {
        id: busy
        running: true
        visible: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        platformStyle: BusyIndicatorStyle {
            period: 800
            numberOfFrames: 5
        }
    }
}