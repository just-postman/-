#include "mysqlmodel.h"

mysqlmodel::mysqlmodel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant mysqlmodel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

int mysqlmodel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int mysqlmodel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant mysqlmodel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
