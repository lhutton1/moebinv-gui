#ifndef CYCLECONTEXTMENU_H
#define CYCLECONTEXTMENU_H

#include <QMenu>
#include <QPointer>
#include <QAction>


class cycleContextMenu : public QMenu
{

public:
    cycleContextMenu();

    QPointer<QAction> isOrthogonal = nullptr;
    QPointer<QAction> isfOrthogonal = nullptr;
    QPointer<QAction> isDifferent = nullptr;
    QPointer<QAction> isTangent = nullptr;
    QPointer<QAction> deletePoint = nullptr;
};

#endif // CYCLECONTEXTMENU_H
