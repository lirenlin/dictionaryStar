#ifndef DATABASE_H
#define DATABASE_H
#include <QString>
#include <QObject>
#include <QList>

class DB: public QObject
{
    Q_OBJECT
public:
    DB(QObject *parent = 0);

    enum status {
        SAME,
        EXIST,
        NO
    };

    Q_INVOKABLE bool addRow(QString name, QString mean, QString dictName);
    Q_INVOKABLE QString dictName(QString name);
    Q_INVOKABLE void removeRow(QString name);
    static bool createConnection();
private:
    status ifExist(QString name, QString dictName = "");
    bool update(QString name, QString mean, QString dictName);
signals:
    void dbChanged();
};

class dbInfo
{
public:
    static const QList<QString> columnNames;
    static const QString tableName ;
    static const QString dbName;
    static const QString dbType;

};

#endif // DATABASE_H
