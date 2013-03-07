/*****************************************************************************
 * dictcore.h - DictionaryStar, stardict dictionary for MeeGo Harmattan      *
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

#ifndef DICTCORE_H
#define DICTCORE_H

#include <QObject>

#include <QStringList>
#include <QPair>
#include <QHash>
#include <QPluginLoader>
#include <QAbstractListModel>

#include "../plugins/dictplugin.h"
#include "tableModel.h"

class DictionariesModel;

/**
 * The DictCore is a base dictionary class.
 */
class DictCore: public QObject
{
    Q_OBJECT

    public:
        Q_PROPERTY(TableModel * table READ table NOTIFY tableChanged)
        /**
         * This class represents a dictionary.
         */
        class Dictionary
        {
            public:
                Dictionary(const QString &plugin, const QString &name)
                    : m_plugin(plugin),
                      m_name(name)
                {  }
                Dictionary()
                { }

                const QString &plugin() const
                { return m_plugin; }
                const QString &name() const
                { return m_name; }
                void setPlugin(const QString &plugin)
                { m_plugin = plugin; }
                void setName(const QString &name)
                { m_name = name; }
                bool operator == (const Dictionary &dict)
                { return m_name == dict.m_name && m_plugin == dict.m_plugin; }

            private:
                QString m_plugin;
                QString m_name;
        };

        /**
         * Construct dictionary.
         */
        DictCore(DictionariesModel& model, QObject *parent = 0);
        /**
         * Destructor.
         */
        ~DictCore();

        /**
         * Returns true if word is exists in dictionaries,
         * otherwise false.
         */
        Q_INVOKABLE bool isTranslatable(const QString &word);

        /**
         * Returns translation for word. If word not found, returns
         * "Not found!"
         */
        Q_INVOKABLE QString translate(const QString &word);

        /**
         * Returns a list of similar words contained in dictionaries.
         */
        Q_INVOKABLE QStringList findSimilarWords(const QString &word);

        /**
         * Returns a sorted list of similar words contained in dictionaries.
         */
        Q_INVOKABLE QStringList listSimilarWords(const QString &word);

        /**
         * Returns a list of available dictionary plugins.
         */
        QStringList availablePlugins() const;

        /**
         * Returns a list of loaded dictionary plugins.
         */
        QStringList loadedPlugins() const
        { return QStringList(m_plugins.keys()); }

        /**
         * Sets a loaded plugins.
         * If plugin cannot be loaded it will not be added to
         * loadedPlugins list.
         */
        void setLoadedPlugins(const QStringList &loadedPlugins);

        /**
         * Returns a list of available dictionaries.
         * The first item in pair is a plugin name, the second item
         * in pair is a dictionary name.
         */
        QList<Dictionary> availableDicts() const;

        /**
         * Returns a list of loaded dictionaries. 
         * The first item in pair is a plugin name, the second item
         * in pair is a dictionary name.
         */
        const QList<Dictionary> &loadedDicts() const
        { return m_loadedDicts; }

        /**
         * Sets a loaded dictionaries.
         * The first item in pair is a plugin name, the second item
         * in pair is a dictionary name.
         * If dictionary cannot be loaded it will not be added to 
         * availableDicts list.
         */
        void setLoadedDicts(const QList<Dictionary> &loadedDicts);

        /**
         * Reload loaded dicts.
         */
        void reloadDicts();

        /**
         * Returns pointer to plugin instance or 0 if not loaded.
         */
        QStarDict::DictPlugin *plugin(const QString &plugin)
        { return m_plugins.contains(plugin) ? qobject_cast<QStarDict::DictPlugin*>(m_plugins[plugin]->instance()) : 0; }

        /**
         * Save settings.
         */
        void saveSettings();

        /**
         * Get the dictionary list for the UI.
         */
        Q_INVOKABLE void updateModel();

        /**
         * (Un)load a dictionary.
         */
        Q_INVOKABLE void enableDictionary(const QString& dict, const QString& plugin, bool enable);

        /**
         * Change the index of an item within the dictionary list.
         */
        Q_INVOKABLE void moveItem(int prevIndex, int newIndex);

        /**
         * Returns true if no dictionaries are loaded.
         */
        Q_INVOKABLE bool noEnabledDictionaries() const;

        /**
         * Enables all dictionaries in the given newline separated list.
         */
        Q_INVOKABLE void enableDictionaries(const QString& list);

        /**
         * Deletes the specified dictionary files from the disk.
         */
        Q_INVOKABLE void deleteDictionary(const QString& pluginName, const QString& dictName);
        
        /**
         * Reports predictive text default setting.
         */
        Q_INVOKABLE bool predictiveText() const;
        
        /**
         * Sets predictive text setting.
         */
        Q_INVOKABLE void setPredictiveText(bool);
        
        /**
         * Reports default dictionary font size.
         */
        Q_INVOKABLE int defaultFontSize() const;
        
        /**
         * Sets default dictionary font size.
         * \param size The desired font pixel size. If negative, removes the setting.
         */
        Q_INVOKABLE void setDefaultFontSize(int size=-1);
        
        /**
         * Reports the font size for lists.
         */
        Q_INVOKABLE int listFontSize() const;
        
        /**
         * Sets the font size to be used for lists.
         * \param size The desired font pixel size. If negative, removes the setting.
         */
        Q_INVOKABLE void setListFontSize(int size=-1);
        
        /**
         * Reports whether back is possible.
         */
        Q_INVOKABLE bool canGoBack() const;
        
        /**
         * Reports whether forward is possible.
         */
        Q_INVOKABLE bool canGoForward() const;
        
        /**
         * Returns the previous word, if any.
         */
        Q_INVOKABLE QString previousWord();
        
        /**
         * Returns the next word, if any.
         */
        Q_INVOKABLE QString nextWord();

        TableModel * table() {return tableModel;}
signals:
        void tableChanged();

    private:

        /**
         * Load settings.
         */
        void loadSettings();
        bool deleteInFolder(const QString& folder, const QString& dictName);
        void deleteFiles(const QString& tdName);

        QHash<QString, QPluginLoader*> m_plugins;
        QList<Dictionary> m_loadedDicts;
        QStringList m_history;
        unsigned int m_current;
        DictionariesModel &m_model;
        TableModel *tableModel; 
};

class DictionariesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DictionaryRoles {
        EnabledRole = Qt::UserRole + 1,
        NameRole,
        PluginRole
    };
    
    DictionariesModel(QObject *parent = 0);
    
    void update(const QList<DictCore::Dictionary> &all, const QList<DictCore::Dictionary> &enabled);
    
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    
private:
    QList<QPair<bool, DictCore::Dictionary> > m_dictionaries;
};

#endif // DICTCORE_H

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab cindent textwidth=120 formatoptions=tc

