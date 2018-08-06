#include <QDebug>
#include "treemodel.h"

treeModel::treeModel(QObject *parent = 0)
    : QStandardItemModel(parent)
{
    qDebug() << "madee";
}
