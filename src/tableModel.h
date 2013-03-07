#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QPair>


typedef QPair<QString, QString> Item;
class TableModel: public QAbstractTableModel
{
    Q_OBJECT

    public:
    TableModel(QObject *parent=0);
    TableModel(QList< QPair<QString, QString> > listofPairs, QObject *parent=0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;

    void addItem(Item);
    void clear();

private:
    QList<Item> listOfPairs;
};

#endif // TABLEMODEL_H
