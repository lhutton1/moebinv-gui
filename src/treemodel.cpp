#include "treemodel.h"

treeModel::treeModel(QObject *parent)
{

}

QVariant treeModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DecorationRole) {
        //QVariant itemData = this->itemFromIndex(index)->data(Qt::DecorationRole);

        return this->itemFromIndex(index)->data(Qt::DecorationRole);
    }

    return QStandardItemModel::data(index, role);

}
