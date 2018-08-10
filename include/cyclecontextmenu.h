#ifndef CYCLECONTEXTMENU_H
#define CYCLECONTEXTMENU_H

#include <QMenu>
#include <QPointer>
#include <QAction>
#include <QObject>
#include <QSignalMapper>

#include "figure.h"

#include "conf.h"

/*!
 * \brief The cycleContextMenu class
 *
 * This class creates a context menu which is then used by each of the
 * cycles created on the scene. It then connects each of the menu items
 * so they function as intended.
 */
class cycleContextMenu : public QMenu
{
    Q_OBJECT

public:
    cycleContextMenu(bool deleteAction = true);

    QPointer<QAction> isOrthogonal = nullptr;
    QPointer<QAction> isfOrthogonal = nullptr;
    QPointer<QAction> isDifferent = nullptr;
    QPointer<QAction> isTangent = nullptr;
    QPointer<QAction> deletePoint = nullptr;

public slots:
    void isChecked(int relType);

signals:
    void addRelationToList(int relType);
    void removeRelationFromList();

};

#endif // CYCLECONTEXTMENU_H
