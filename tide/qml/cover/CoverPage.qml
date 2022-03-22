/*****************************************************************************
 *
 * Created: 2016 by Eetu Kahelin / eekkelund
 *
 * Copyright 2016 Eetu Kahelin. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
*****************************************************************************/
import QtQuick 2.2
import Sailfish.Silica 1.0

CoverBackground {
        Image {
                source: "../icons/cover-tide.png"
                asynchronous: true
                width: parent.width
                anchors.left: parent.left
                anchors.top:parent.top
                anchors.topMargin: Theme.paddingLarge
                anchors.leftMargin: -Theme.paddingLarge
                fillMode: Image.PreserveAspectFit
                opacity: 0.15
            }
        Column {
            anchors { top: parent.top
                topMargin: Theme.paddingMedium
                horizontalCenter: parent.horizontalCenter
                leftMargin: Theme.paddingLarge
                rightMargin: Theme.paddingLarge
            }
            height: label.height
        Label {
                id:label
            font.pixelSize: Theme.fontSizeLarge
            font.family: Theme.fontFamilyHeading
            text: rootMode ? "root@tIDE" : editorMode ? "tIDEditor":"tIDE"
        }
        }
}


