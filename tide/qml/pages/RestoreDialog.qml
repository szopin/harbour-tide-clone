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
import io.thp.pyotherside 1.3


Dialog{
    property string pathToFile
    Column{
        width: parent.width
        DialogHeader {}
        Label{
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Restore autosaved version?")
        }
    }
    onDone: {
        if (result == DialogResult.Accepted) {
            py.call('editFile.openAutoSaved', [pathToFile], function(result) {
                documentHandler.text = result.text;
                fileTitle=result.fileTitle
                previousPath=pathToFile.substring(0,pathToFile.lastIndexOf('/'))
            })
            fullFilePath=pathToFile
        }else if(result == DialogResult.Rejected){
            py.call('editFile.openings', [pathToFile], function(result) {
                documentHandler.text = result.text;
                fileTitle=result.fileTitle
                if(highlight) documentHandler.setDictionary(fileType);
                py.call('editFile.savings', [pathToFile,result.text], function(result) {
                    fileTitle=result
                });
            })
            fullFilePath=pathToFile
        }
    }

}
