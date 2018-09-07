#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QSettings>
#include <QStandardItemModel>


class treeModel : public QStandardItemModel
{
    Q_OBJECT

public:
    treeModel(QObject *parent = nullptr);
    virtual QVariant data(const QModelIndex &index, int role) const;
};

#endif // TREEMODEL_H
