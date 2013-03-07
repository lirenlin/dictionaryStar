/*****************************************************************************
 * dictcore.cpp - DictionaryStar, stardict dictionary for MeeGo Harmattan    *
 * Copyright (C) 2008 Alexander Rodin (under QStarDict)                      *
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

#include "dictcore.h"

#include <QApplication>
#include <QFileInfoList>
#include <QFileInfo>
#include <QDir>
#include <QRegExp>
#include <QSettings>
#include <QDebug>
#include <QPluginLoader>
#include "../plugins/dictplugin.h"

namespace {
    const QString BookNameTag("bookname=");
    const unsigned int MaxBookNameLength = 1024;
}

DictCore::DictCore(DictionariesModel& model, QObject *parent)
    : QObject(parent),
    m_current(0),
    m_model(model)
{
    tableModel = new TableModel(parent);
    loadSettings();
}

DictCore::~DictCore()
{
    saveSettings();
    foreach (QPluginLoader *loader, m_plugins)
    {
        delete loader->instance();
        delete loader;
    }
}

bool DictCore::isTranslatable(const QString &word)
{
    QString simplifiedWord = word.simplified();
    for (QList<Dictionary>::const_iterator i = m_loadedDicts.begin(); i != m_loadedDicts.end(); ++i)
    {
        if (! m_plugins.contains(i->plugin()))
            continue;
        if (qobject_cast<QStarDict::DictPlugin*>(m_plugins[i->plugin()]->instance())->isTranslatable(i->name(), simplifiedWord))
            return true;
    }
    return false;
}

QString DictCore::translate(const QString &word)
{
    tableModel->clear();
    QString simplifiedWord = word.simplified();
    QString result = "<style>.dict_name { font-size: small; font-style: italic; color: green; } .title { font-size: large; font-weight: bold; }</style>";
    for (QList<Dictionary>::const_iterator i = m_loadedDicts.begin(); i != m_loadedDicts.end(); ++i)
    {
        if (! m_plugins.contains(i->plugin()))
            continue;
        QStarDict::DictPlugin *plugin = qobject_cast<QStarDict::DictPlugin*>(m_plugins[i->plugin()]->instance());
        if (! plugin->isTranslatable(i->name(), simplifiedWord))
            continue;
        QStarDict::DictPlugin::Translation translation = plugin->translate(i->name(), simplifiedWord);
        result += "<p>\n"
            "<font class=\"dict_name\">" + translation.dictName() + "</font><br>\n"
            "<font class=\"title\">" + translation.title() + "</font><br>\n"
            + translation.translation() + "</p>\n";

        tableModel->addItem(Item(translation.dictName(), translation.translation()));
    }
    if(m_current < 1 || m_history.isEmpty() || m_history.at(m_current-1) != simplifiedWord ) {
        while((unsigned)m_history.size() > m_current)
            m_history.removeLast();
        m_history.append(simplifiedWord);
        m_current++;
    }
    emit tableChanged();
    return result;
}

QStringList DictCore::findSimilarWords(const QString &word)
{
    QString simplifiedWord = word.simplified();
    QStringList result;
    for (QList<Dictionary>::const_iterator i = m_loadedDicts.begin(); i != m_loadedDicts.end(); ++i)
    {
        if (! m_plugins.contains(i->plugin()))
            continue;
        QStarDict::DictPlugin *plugin = qobject_cast<QStarDict::DictPlugin*>(m_plugins[i->plugin()]->instance());
        if (! plugin->features().testFlag(QStarDict::DictPlugin::SearchSimilar))
            continue;
        QStringList similar = plugin->findSimilarWords(i->name(), simplifiedWord);
        for (QStringList::const_iterator j = similar.begin(); j != similar.end(); ++j)
            if (! result.contains(*j, Qt::CaseSensitive))
                result << *j;
    }
    return result;
}

QStringList DictCore::availablePlugins() const
{
    QStringList result;
#ifdef Q_WS_X11
    QFileInfoList files = QDir(DICTSTAR_PLUGINS_DIR).entryInfoList(QStringList("lib*.so"),
                  QDir::Files | QDir::NoDotAndDotDot);
    for (QFileInfoList::const_iterator i = files.begin(); i != files.end(); ++i)
        result << i->fileName().mid(3, i->fileName().length() - 6);
#elif defined Q_WS_WIN
    QFileInfoList files = QDir(DICTSTAR_PLUGINS_DIR).entryInfoList(QStringList("*0.dll"),
                  QDir::Files | QDir::NoDotAndDotDot);
    for (QFileInfoList::const_iterator i = files.begin(); i != files.end(); ++i)
        result << i->fileName().left(i->fileName().length() - 5);
#elif defined Q_WS_MAC
    QStringList macFilters;
    // various Qt versions...
    macFilters << "*.dylib" << "*.bundle" << "*.so";
    QString binPath = QCoreApplication::applicationDirPath();
    // navigate through mac's bundle tree structore
    QDir d(binPath + "/../lib/");
    QFileInfoList files = d.entryInfoList(macFilters,
                                          QDir::Files | QDir::NoDotAndDotDot);
    for (QFileInfoList::const_iterator i = files.begin(); i != files.end(); ++i) {
        result << i->fileName();
    }
#else
#error "Function DictCore::availablePlugins() is not implemented on this platform"
#endif
    return result;
}

void DictCore::setLoadedPlugins(const QStringList &loadedPlugins)
{
    for (QHash <QString, QPluginLoader*>::iterator i = m_plugins.begin(); i != m_plugins.end(); ++i)
    {
        delete (*i)->instance();
        delete *i;
    }
    m_plugins.clear();

    for (QStringList::const_iterator i = loadedPlugins.begin(); i != loadedPlugins.end(); ++i)
    {
#ifdef Q_WS_X11
        QString pluginFilename = static_cast<QString>(DICTSTAR_PLUGINS_DIR) + "/" "lib" + *i + ".so";
#elif defined Q_WS_WIN
        QString pluginFilename = static_cast<QString>(DICTSTAR_PLUGINS_DIR) + "/" + *i + "0.dll";
#elif defined Q_WS_MAC
        // here we need to follow mac's bundle tree...
        QString pluginFilename = QDir(QCoreApplication::applicationDirPath()+"/../lib/"+*i).absolutePath();
#else
#error "Function DictCore::setLoadedPlugins(const QStringList &loadedPlugins) is not available on this platform"
#endif
        QPluginLoader *plugin = new QPluginLoader(pluginFilename);
        if (! plugin->load())
        {
            qWarning() << plugin->errorString();
            delete plugin;
            continue;
        }
        m_plugins[*i] = plugin;
    }
}

QList<DictCore::Dictionary> DictCore::availableDicts() const
{
    QList<Dictionary> result;
    for (QHash<QString, QPluginLoader*>::const_iterator i = m_plugins.begin(); i != m_plugins.end(); ++i)
    {
        QStarDict::DictPlugin *plugin = qobject_cast<QStarDict::DictPlugin*>((*i)->instance());
        QStringList dicts = plugin->availableDicts();
        for (QStringList::const_iterator j = dicts.begin(); j != dicts.end(); ++j)
            result << Dictionary(i.key(), *j);
    }
    return result;
}

void DictCore::setLoadedDicts(const QList<Dictionary> &loadedDicts)
{
    QHash<QString, QStringList> dicts;
    for (QList<Dictionary>::const_iterator i = loadedDicts.begin(); i != loadedDicts.end(); ++i)
        dicts[i->plugin()] << i->name();
    for (QHash<QString, QStringList>::const_iterator i = dicts.begin(); i != dicts.end(); ++i)
    {
        if (! m_plugins.contains(i.key()))
            continue;
        QStarDict::DictPlugin *plugin = qobject_cast<QStarDict::DictPlugin*>(m_plugins[i.key()]->instance());
        plugin->setLoadedDicts(*i);
        dicts[i.key()] = plugin->loadedDicts();
    }
    m_loadedDicts.clear();
    for (QList<Dictionary>::const_iterator i = loadedDicts.begin(); i != loadedDicts.end(); ++i)
        if (dicts.contains(i->plugin()) && dicts[i->plugin()].contains(i->name()))
            m_loadedDicts << *i;
}

void DictCore::saveSettings()
{
    QSettings config;
    config.setValue("DictCore/loadedPlugins", loadedPlugins());
    QStringList rawDictsList;
    for (QList<Dictionary>::const_iterator i = m_loadedDicts.begin(); i != m_loadedDicts.end(); ++i)
        rawDictsList << i->plugin() << i->name();
    config.setValue("DictCore/loadedDicts", rawDictsList);
}

void DictCore::loadSettings()
{
    QSettings config;
    setLoadedPlugins(config.value("DictCore/loadedPlugins", availablePlugins()).toStringList());
    QStringList rawDictsList = config.value("DictCore/loadedDicts").toStringList();
    if (rawDictsList.isEmpty())
        setLoadedDicts(availableDicts());
    else
    {
        QList<Dictionary> dicts;
        for (QStringList::const_iterator i = rawDictsList.begin(); i != rawDictsList.end(); i += 2)
            dicts << Dictionary(*i, *(i + 1));
        setLoadedDicts(dicts);
    }
}

void DictCore::reloadDicts()
{
    QList<Dictionary> loaded;
    for (QHash<QString, QPluginLoader*>::const_iterator i = m_plugins.begin(); i != m_plugins.end(); ++i)
    {
        QStarDict::DictPlugin *plugin = qobject_cast<QStarDict::DictPlugin*>((*i)->instance());
        plugin->setLoadedDicts(plugin->loadedDicts());
        QStringList loadedNames = plugin->loadedDicts();
        for (QStringList::const_iterator j = loadedNames.begin(); j != loadedNames.end(); ++j)
            loaded << Dictionary(i.key(), *j);
    }
    QList<Dictionary> oldLoaded = m_loadedDicts;
    m_loadedDicts.clear();
    for (QList<Dictionary>::iterator i = oldLoaded.begin(); i != oldLoaded.end(); ++i)
        if (loaded.contains(*i))
            m_loadedDicts << *i;
}

QStringList DictCore::listSimilarWords(const QString &word)
{
    QStringList result = findSimilarWords(word);
    //result.sort();
    result.removeDuplicates();
    return result;
}

void DictCore::updateModel()
{
    m_model.update(availableDicts(), m_loadedDicts);
}

void DictCore::moveItem(int prevIndex, int newIndex)
{
    if(prevIndex < 0 || newIndex < 0)
        return;
    if(prevIndex < m_loadedDicts.size()) {
        if(newIndex > m_loadedDicts.size())
            newIndex = m_loadedDicts.size()-1;
        Dictionary dict = m_loadedDicts.takeAt(prevIndex);
        m_loadedDicts.insert(newIndex, dict);
        saveSettings();
        updateModel();
    }
}

void DictCore::enableDictionary(const QString& dict, const QString& pluginName, bool enable)
{
    QList<Dictionary> loadedDicts = m_loadedDicts;
    if(enable && !loadedDicts.contains(Dictionary(pluginName, dict))) {
        loadedDicts.append(Dictionary(pluginName, dict));
    } else {
        loadedDicts.removeAll(Dictionary(pluginName, dict));
    }
    setLoadedDicts(loadedDicts);
    saveSettings();
    updateModel();
}

bool DictCore::noEnabledDictionaries() const
{
    return m_loadedDicts.isEmpty();
}

void DictCore::enableDictionaries(const QString& list)
{
    QStringList dicts(list.split("\n"));
    foreach(const QString &dict, dicts)
        enableDictionary(dict, "stardict", true);
    updateModel();
}

void DictCore::deleteDictionary(const QString& pluginName, const QString& dictName)
{
    if(pluginName != "stardict")
        return;
    QString path=QDir::homePath();
    path.append("/.stardict/dic");
    if(!QDir(path).exists())
        return;
    deleteInFolder(path, dictName);
}

bool DictCore::deleteInFolder(const QString& folder, const QString& dictName)
{
    QDir delDir(folder);
    QStringList filter;
    filter << "*.ifo";
    QString tdName;
    foreach(QFileInfo fi, delDir.entryInfoList(filter, QDir::Files)) {
        QString fn = fi.absoluteFilePath();
        QFile f(fn);
        if(!f.open(QIODevice::ReadOnly))
            qWarning() << "ERROR reading ifo file" << fn;
        else {
            while(!f.atEnd()) {
                QString str = QString::fromUtf8(f.readLine(MaxBookNameLength)).simplified();
                if(str.startsWith(BookNameTag, Qt::CaseInsensitive)) {
                    if(!dictName.compare(str.mid(BookNameTag.length()))) {
                        tdName = fn.mid(0, fn.lastIndexOf(".ifo"));
                    }
                    f.close();
                    if(!tdName.isEmpty()) {
                        deleteFiles(tdName);
                        updateModel();
                        return true;
                    }
                }
            }
        }
    }
    foreach(QFileInfo path, delDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        if(deleteInFolder(path.absoluteFilePath(), dictName)) {
            delDir.rmdir(path.fileName());
            return true;
        }
    }
    return false;
}

void DictCore::deleteFiles(const QString& baseName) {
    QString ifoName = QString("%1.ifo").arg(baseName);
    QString dzName = QString("%1.dict.dz").arg(baseName);
    QString idxName = QString("%1.idx").arg(baseName);
    QString oftName = QString("%1.oft").arg(idxName);
    qDebug() << "Deleting" << baseName;
    QFile::remove(oftName);
    QFile::remove(idxName);
    QFile::remove(dzName);
    QFile::remove(ifoName);
}

bool DictCore::predictiveText() const
{
    QSettings config;
    return config.value("DictCore/predictiveText", false).toBool();
}

void DictCore::setPredictiveText(bool enable)
{
    QSettings config;
    config.setValue("DictCore/predictiveText", enable);
}

int DictCore::defaultFontSize() const
{
    QSettings config;
    return config.value("DictCore/defaultFontSize", 20).toInt();
}

void DictCore::setDefaultFontSize(int size)
{
    QSettings config;
    if(size < 0)
        config.remove("DictCore/defaultFontSize");
    else
        config.setValue("DictCore/defaultFontSize", size);
}

int DictCore::listFontSize() const
{
    QSettings config;
    return config.value("DictCore/listFontSize", 25).toInt();
}

void DictCore::setListFontSize(int size)
{
    QSettings config;
    if(size < 0)
        config.remove("DictCore/listFontSize");
    else
        config.setValue("DictCore/listFontSize", size);
}

bool DictCore::canGoBack() const
{
    return (m_current > 1);
}

bool DictCore::canGoForward() const
{
    return ((unsigned)m_history.size() > m_current);
}

QString DictCore::previousWord()
{
    if(m_current <= 0)
        return QString();
    return m_history.at(--m_current-1);
}

QString DictCore::nextWord()
{
    if(m_current >= (unsigned)m_history.size())
        return QString();
    return m_history.at(m_current++);
}

DictionariesModel::DictionariesModel(QObject *parent)
: QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[EnabledRole] = "useDict";
    roles[NameRole] = "name";
    roles[PluginRole] = "plugin";
    setRoleNames(roles);
}

void DictionariesModel::update(const QList<DictCore::Dictionary> &all, const QList<DictCore::Dictionary> &enabled)
{
    beginResetModel();
    m_dictionaries.clear();
    endResetModel();
    
    if(all.isEmpty())
        return;
    
    beginInsertRows(QModelIndex(), 0, 0);
    for (QList<DictCore::Dictionary>::const_iterator i = enabled.begin(); i != enabled.end(); ++i)
        m_dictionaries << QPair<bool, DictCore::Dictionary>(true, *i);
    for (QList<DictCore::Dictionary>::const_iterator i = all.begin(); i != all.end(); ++i) {
        if(!enabled.contains(*i))
            m_dictionaries << QPair<bool, DictCore::Dictionary>(false, *i);
    }
    endInsertRows();
}

int DictionariesModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_dictionaries.count();
}

QVariant DictionariesModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() > rowCount())
        return QVariant();
    
    if(role == EnabledRole)
        return m_dictionaries.at(index.row()).first;
    
    const DictCore::Dictionary &dict = m_dictionaries.at(index.row()).second;

    if(role == NameRole)
        return dict.name();
    else if(role == PluginRole)
        return dict.plugin();
    
    return QVariant();
}

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent textwidth=120 formatoptions=tc

