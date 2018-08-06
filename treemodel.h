#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QStandardItemModel>

class treeModel : public QStandardItemModel
{
    Q_OBJECT

public:
    treeModel(QObject *parent = 0);
};

#endif
