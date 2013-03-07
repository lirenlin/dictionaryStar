/*****************************************************************************
 * main.cpp - DictionaryStar, stardict dictionary for MeeGo Harmattan        *
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
#include <QtGui/QApplication>
#include <QDeclarativeContext>
#include <QtDeclarative>
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QDeclarativeView>
#include <MDeclarativeCache>

#include <dictcore.h>
#include "dictwebview.h"
#include "tableModel.h"
#include "database.h"
#include "sqlmodel.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication *app = MDeclarativeCache::qApplication(argc, argv);
    QDeclarativeView *view = MDeclarativeCache::qDeclarativeView();
    DictionariesModel model;
    DictCore *core = new DictCore(model);
    qmlRegisterType<TableModel>("com.lirenlin.tableModel", 1, 0, "TableModel");

    DB::createConnection();
    DB *db = new DB(app);
    view->rootContext()->setContextProperty("db", db);

    sqlQueryModel *queryModel = new sqlQueryModel(app);
    queryModel->setQuery("SELECT * FROM word");
    view->rootContext()->setContextProperty("listModel", queryModel);

    QString locale = QLocale::system().name();
    QTranslator translator;
    if (translator.load("DictionaryStar-" + locale, ":/translations/"))
      app->installTranslator(&translator);

    qmlRegisterType<DictWebView>("DictWebLib", 1, 0, "DictWebView");
#if QT_VERSION < 0x040702
    view->setAttribute(static_cast<Qt::WidgetAttribute>(130), true);
#else
    view->setAttribute(Qt::WA_AutoOrientation, true);
#endif
    view->setAttribute(Qt::WA_NoSystemBackground);
    view->rootContext()->setContextProperty("dictCore", core);
    view->rootContext()->setContextProperty("dictsModel", &model);
    view->setSource(QUrl(QString::fromLatin1("%1/../%2").arg(QCoreApplication::applicationDirPath(), "qml/main.qml")));
    view->showFullScreen();

    app->exec();
    delete core;
    delete view;
    delete app;
}
