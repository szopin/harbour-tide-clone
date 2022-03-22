/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Quick Controls module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
** *
 * Changes: 2016-2017 by Eetu Kahelin / eekkelund
 *
 * Copyright 2016-2017 Eetu Kahelin. All rights reserved.
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

#include "documenthandler.h"

#include <QtGui/QTextDocument>
#include <QtGui/QTextCursor>
#include <QtGui/QFontDatabase>
#include <QtCore/QFileInfo>
#include <QTextLayout>

DocumentHandler::DocumentHandler() : m_target(0)  , m_doc(0) , m_cursorPosition(-1) , m_selectionStart(0) , m_selectionEnd(0) , m_realhighlighter(0)
{
}

QQuickItem *DocumentHandler::target() const
{
    return m_target;
}

int DocumentHandler::cursorPosition() const
{
    return m_cursorPosition;
}

int DocumentHandler::selectionStart() const
{
    return m_selectionStart;
}

int DocumentHandler::selectionEnd() const
{
    return m_selectionEnd;
}

QString DocumentHandler::text() const
{
    return m_text;
}

QStringList DocumentHandler::lines() const
{
    QStringList lines;
    for (QTextBlock tb = m_doc->begin(); tb != m_doc->end(); tb = tb.next()){
        const int nbLines = tb.layout()->lineCount();
        lines.append(QString::number(tb.blockNumber()+1));
        for (int i=1; i < nbLines; i++){
            lines.append(" ");
        }
    }
    return lines;
}

void DocumentHandler::setTarget(QQuickItem *target)
{
    m_doc = 0;
    m_realhighlighter = 0;
    m_target = target;
    if (!m_target)
        return;
    QVariant doc = m_target->property("textDocument");
    if (doc.canConvert<QQuickTextDocument*>()) {
        QQuickTextDocument *qqdoc = doc.value<QQuickTextDocument*>();
        if (qqdoc)
            m_doc = qqdoc->textDocument();
        m_realhighlighter = new RealHighlighter(m_doc);
    }
    connect(m_doc, SIGNAL(blockCountChanged()), this, SLOT(lines()));
    emit targetChanged();
}

void DocumentHandler::setCursorPosition(int position)
{
    if (m_cursorPosition == position)
        return;

    m_cursorPosition = position;
}

void DocumentHandler::setSelectionStart(int position)
{
    m_selectionStart = position;
}

void DocumentHandler::setSelectionEnd(int position)
{
    m_selectionEnd = position;
}

void DocumentHandler::setText(QString &arg)
{
    if (m_text == arg)
        return;

    m_text = arg;
    emit textChanged();
}

void DocumentHandler::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
}
void DocumentHandler::setStyle(QString primaryColor, QString secondaryColor, QString highlightColor, QString secondaryHighlightColor, QString highlightBackgroundColor, QString highlightDimmerColor, qreal m_baseFontPointSize)
{
    if (m_realhighlighter) {
        m_realhighlighter->setStyle(primaryColor, secondaryColor, highlightColor, secondaryHighlightColor, highlightBackgroundColor, highlightDimmerColor, m_baseFontPointSize);
    }
}

void DocumentHandler::setDictionary(QString dictionary)
{
    if (m_realhighlighter) {
        m_realhighlighter->setDictionary(dictionary);
    }
}

void DocumentHandler::searchHighlight(QString str)
{
    if (m_realhighlighter) {
        m_realhighlighter->searchHighlight(str);
    }
}

void DocumentHandler::enableHighlight(bool enable)
{
    if (m_realhighlighter) {
        m_realhighlighter->enableHighlight(enable);
    }
}

QTextCursor DocumentHandler::textCursor() const
{
    QTextCursor cursor = QTextCursor(m_doc);
    if (m_selectionStart != m_selectionEnd) {
        cursor.setPosition(m_selectionStart);
        cursor.setPosition(m_selectionEnd, QTextCursor::KeepAnchor);
    } else {
        cursor.setPosition(m_cursorPosition);
    }
    return cursor;
}
