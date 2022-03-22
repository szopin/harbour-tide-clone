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

#include "filewatcher.h"

FileWatcher::FileWatcher()
{
    watcher=0;
    watcher = new QFileSystemWatcher(this);
    connect(watcher, SIGNAL(fileChanged(const QString &)), this, SLOT(fileChanged(const QString &)));
    connect(watcher, SIGNAL(directoryChanged(const QString &)), this, SLOT(directoryChanged(const QString &)));
    watcher->addPath("/var/lib/harbour-tide-keyboard/config/");
    watcher->addPath("/var/lib/harbour-tide-keyboard/config/config.conf");
}

void FileWatcher::directoryChanged(const QString & path)
{
}
//checks if config file is changed=different filetype opened
void FileWatcher::fileChanged(const QString & path)
{
    QFileInfo checkFile(path);
    QSettings settings(QString(path), QSettings::IniFormat);
    QString type = settings.value("fileType/type", "qml").toString();
    emit changed(type);
    while(!checkFile.exists()){}
    watcher->addPath(path);
}
