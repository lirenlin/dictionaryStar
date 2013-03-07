#ifndef SQLMODEL_H
#define SQLMODEL_H

#include <QVariant>
#include <QObject>
#include <QSqlQueryModel>

class sqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit sqlQueryModel(QObject *parent);
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount( const QModelIndex &parent) const;
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void loadDB(); 
signals:
public slots:
private:
    const static char* COLUMN_NAMES[];
    const static char* SQL_SELECT;
    int removeTimes;

};


#endif // SQLMODEL_H
