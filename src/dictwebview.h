/*****************************************************************************
 * dictwebview.h - DictionaryStar, stardict dictionary for MeeGo Harmattan   *
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

#ifndef DICTWEBVIEW_H
#define DICTWEBVIEW_H

#include <QWebView>
#include <QGraphicsProxyWidget>
#include <QFile>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QProgressDialog>

class DictWebView : public QGraphicsProxyWidget
{
    Q_OBJECT
    Q_PROPERTY(QUrl url READ url WRITE setUrl)
    Q_PROPERTY(int contentHeight READ contentHeight WRITE setContentHeight)
    Q_PROPERTY(int contentWidth READ contentWidth WRITE setContentWidth)
    Q_PROPERTY(qreal preferredHeight READ preferredHeight WRITE setPreferredHeight)
    Q_PROPERTY(qreal preferredWidth READ preferredWidth WRITE setPreferredWidth)
    Q_PROPERTY(qreal zoomFactor READ zoomFactor WRITE setZoomFactor)
public:
    explicit DictWebView(QGraphicsProxyWidget *parent = 0);

    Q_INVOKABLE void load(const QString& url);
    QUrl url() const;
    void setUrl(const QUrl& url);
    int contentHeight() const;
    void setContentHeight(int);
    int contentWidth() const;
    void setContentWidth(int);
    qreal zoomFactor() const;
    void setZoomFactor(qreal);

signals:
    void downloadProgress(qint64 current, qint64 total);
    void importCompleted(const QString& dicts);
    void contentSizeChanged();
    void linkClicked();
    void loadFinished();
    void movePage(bool back); //! back with true, forward with false
    void hideButton(bool back); //! back button is true, forward is false

public slots:
    void followLink(const QUrl &);
    void extractFile();
    void handleContent(QNetworkReply*);
    void handleContent(const QNetworkRequest&);
    void handleMove(bool);

private:
    void downloadFile(const QUrl&);

    QNetworkReply* m_Reply;
    QWebView* webView;
};

#endif // DICTWEBVIEW_H
