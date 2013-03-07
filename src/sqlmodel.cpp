#include "sqlmodel.h"
#include <QHash>

sqlQueryModel::sqlQueryModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    int idx = 0;
    QHash<int, QByteArray> roleNames;
    while( COLUMN_NAMES[idx]) {
            roleNames[Qt::UserRole + idx + 1] = COLUMN_NAMES[idx];
            idx++;
    }
    setRoleNames(roleNames);
    //refresh();
}

QVariant sqlQueryModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    if(role < Qt::UserRole)
    {
        value = QSqlQueryModel::data(index, role);
    }
    else
    {
        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
    }
    return value;
}

void sqlQueryModel::loadDB()
{
    setQuery("SELECT * FROM word");
    removeTimes = 0;
}
void sqlQueryModel::remove(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    QAbstractItemModel::removeRow(row);
    ++removeTimes;
    endRemoveRows();
}
int sqlQueryModel::rowCount( const QModelIndex &parent) const
{
    return QSqlQueryModel::rowCount() - removeTimes;

}

const char* sqlQueryModel::COLUMN_NAMES[] = {
 "ID", "name", "mean", "date", "dictName"
};
const char* sqlQueryModel::SQL_SELECT =
        "SELECT * FROM word";
