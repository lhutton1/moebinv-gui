#include "treemodel.h"

treeModel::treeModel(QObject *parent)
{

}


/*!
 * \brief treeModel::data reimplements data() function to display colour.
 * \param index index of an item in the tree.
 * \param role display role.
 * \return QVariant
 *
 * This function reimplements the data() function from QStandardItemModel
 * so that it returns a square next to the label representing the colour the
 * cycle is displayed in, in the graphics view.
 */
QVariant treeModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DecorationRole) {
        return this->itemFromIndex(index)->data(Qt::DecorationRole);
    }

    return QStandardItemModel::data(index, role);
}
