/*****************************************************************************
 * dictwebview.cpp - DictionaryStar, stardict dictionary for MeeGo Harmattan *
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
#include "dictwebview.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QWebFrame>
#include <QWebHistory>
#include "qwebviewselectionsuppressor.h"

#include <archive.h>
#include <archive_entry.h>

namespace {
    const QString BookNameTag("bookname=");
    const unsigned int MaxBookNameLength = 1024;
}

DictWebView::DictWebView(QGraphicsProxyWidget *parent) :
    QGraphicsProxyWidget(parent),
    m_Reply(0)
{
    webView = new QWebView();
    webView->settings()->setAttribute(QWebSettings::FrameFlatteningEnabled, true);
    webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    webView->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    webView->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    webView->page()->setForwardUnsupportedContent(true);
    webView->page()->setContentEditable(false);
    connect(webView, SIGNAL(linkClicked(QUrl)), this, SLOT(followLink(QUrl)));
    connect(webView, SIGNAL(linkClicked(QUrl)), this, SIGNAL(linkClicked()));
    connect(webView, SIGNAL(loadFinished(bool)), this, SIGNAL(loadFinished()));
    connect(webView->page()->mainFrame(), SIGNAL(contentsSizeChanged(QSize)), this, SIGNAL(contentSizeChanged()));
    connect(webView->page(), SIGNAL(unsupportedContent(QNetworkReply*)), this, SLOT(handleContent(QNetworkReply*)));
    connect(webView->page(), SIGNAL(downloadRequested(QNetworkRequest)), this, SLOT(handleContent(QNetworkRequest)));
    connect(this, SIGNAL(movePage(bool)), this, SLOT(handleMove(bool)));
    QWebViewSelectionSuppressor *suppressor = new QWebViewSelectionSuppressor(webView);
    setWidget(webView);
}

void DictWebView::handleMove(bool back)
{
    if(back)
        webView->back();
    else
        webView->forward();
    
    webView->repaint();
    if(back && !webView->page()->history()->canGoBack())
        emit hideButton(true);
    else if(!back && !webView->page()->history()->canGoForward())
        emit hideButton(false);
}

QUrl DictWebView::url() const
{
    return webView->url();
}

void DictWebView::setUrl(const QUrl &url)
{
    webView->setUrl(url);
}

void DictWebView::load(const QString& url)
{
    qDebug() << "Loading" << url;
    webView->load(url);
}

int DictWebView::contentHeight() const
{
    return webView->page()->mainFrame()->contentsSize().height();
}

void DictWebView::setContentHeight(int height)
{
    setPreferredHeight(height);
}

int DictWebView::contentWidth() const
{
    return webView->page()->mainFrame()->contentsSize().width();
}

void DictWebView::setContentWidth(int width)
{
    setPreferredWidth(width);
}

qreal DictWebView::zoomFactor() const
{
    return webView->zoomFactor();
}

void DictWebView::setZoomFactor(qreal factor)
{
    webView->setZoomFactor(factor);
}

void DictWebView::followLink(const QUrl& url)
{
    qDebug() << "Following link" <<  url.toString();
    webView->load(url);
}

void DictWebView::handleContent(const QNetworkRequest& request)
{
    handleContent(webView->page()->networkAccessManager()->get(request));
}

void DictWebView::handleContent(QNetworkReply * reply)
{
    QString contentType = reply->header(QNetworkRequest::ContentTypeHeader).toString();
    if(contentType == "application/x-bzip2" || contentType == "application/x-gzip"
            || contentType == "application/x-tar" || contentType == "application/zip"
            || contentType == "application/octet-stream") {
        if(m_Reply) {
            m_Reply->abort();
            m_Reply->deleteLater();
        }
        m_Reply = reply;
        connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(downloadProgress(qint64,qint64)));
        connect(reply, SIGNAL(finished()), this, SLOT(extractFile()));
    } else
        qDebug() << "Unsupported content:" << reply->header(QNetworkRequest::ContentTypeHeader);
}

struct archive *openArchive(const QString& fileName)
{
    struct archive *ar = archive_read_new();
    bool res = true;
    if(archive_read_support_compression_all(ar) != ARCHIVE_OK) {
        qWarning() << "ERROR with archive compression support";
        res = false;
    }
    if(res && archive_read_support_format_all(ar) != ARCHIVE_OK) {
        qWarning() << "ERROR with archive format support";
        res = false;
    }
    if(res && archive_read_open_filename(ar, fileName.toUtf8().constData(), 1024) != ARCHIVE_OK) {
        qWarning() << "ERROR opening archive";
        res = false;
    }
    if(!res)
        return NULL;
    return ar;
}

void DictWebView::extractFile()
{
    QString url = m_Reply->header(QNetworkRequest::LocationHeader).toString();
    if(url.isEmpty()) {
        url = m_Reply->request().url().toString();
    }
    qDebug() << "extractFile()" << url;

    QString path=QDir::homePath();
    path.append("/.stardict/dic");
    if(!QDir(path).exists()) {
        QDir().mkdir(path.left(path.lastIndexOf("/")));
        QString otherPath(QDir::homePath());
        otherPath.append("/MyDocs/.dict");
        if(!QDir(otherPath).exists())
            QDir().mkdir(otherPath);
        QFile::link(otherPath, path);
    }
    path.append("/");
    QString fileName = url.mid(url.lastIndexOf("/")+1);
    fileName.prepend(path);

    QFile myFile(fileName);
    if(!myFile.open(QIODevice::WriteOnly)) {
        qWarning() << "ERROR opening file" << fileName;
        emit importCompleted(QString());
        return;
    }
    myFile.write(m_Reply->readAll());
    myFile.close();
    m_Reply->deleteLater();
    m_Reply = 0;

    QStringList dicts;
    QString pwd = QDir::currentPath();
    QDir::setCurrent(path);
    struct archive *ar = openArchive(fileName);
    struct archive_entry *entry;
    bool found = false;
    // First check that this is indeed a stardict dictionary
    while (ar && !found && archive_read_next_header(ar, &entry) == ARCHIVE_OK) {
        QString fn=archive_entry_pathname(entry);
        if(fn.endsWith(".ifo", Qt::CaseInsensitive)) {
            found = true;
            break;
        }
    }
    if(found)
        ar = openArchive(fileName);
    else
        qDebug() << "Not a stardict archive:" << fileName;

    while (found && ar && archive_read_next_header(ar, &entry) == ARCHIVE_OK) {
        qDebug() << QString::fromUtf8(archive_entry_pathname(entry));
        if(archive_read_extract(ar, entry, ARCHIVE_EXTRACT_PERM|ARCHIVE_EXTRACT_TIME) != ARCHIVE_OK) {
            qWarning() << "ERROR reading data from" << QString::fromUtf8(archive_entry_pathname(entry));
            found = false;
        } else {
            QString fn = QString::fromUtf8(archive_entry_pathname(entry));
            if(fn.endsWith(".ifo", Qt::CaseInsensitive)) {
                QFile f(fn);
                if(!f.open(QIODevice::ReadOnly))
                    qWarning() << "ERROR reading ifo file" << fn;
                else {
                    while(!f.atEnd()) {
                        QString str=QString::fromUtf8(f.readLine(MaxBookNameLength)).simplified();
                        if(str.startsWith(BookNameTag, Qt::CaseInsensitive)) {
                            dicts.append(str.mid(BookNameTag.length()));
                            qDebug() << "found:"<<str.mid(BookNameTag.length());
                            break;
                        }
                    }
                    f.close();
                }
            }
        }
    }

    archive_read_finish(ar);
    QDir::setCurrent(pwd); // back to where we were

    // Remove the archive
    QFile::remove(fileName);

    emit importCompleted(dicts.join("\n"));
}
