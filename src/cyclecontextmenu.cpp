#include "cyclecontextmenu.h"

cycleContextMenu::cycleContextMenu()
{
    isOrthogonal = new QAction("Orthogonal", this);
    isOrthogonal->setCheckable(true);
    isOrthogonal->setChecked(false);
    this->addAction(isOrthogonal);

    isfOrthogonal = new QAction("F-Orthogonal", this);
    isfOrthogonal->setCheckable(true);
    isfOrthogonal->setChecked(false);
    this->addAction(isfOrthogonal);


    isDifferent = new QAction("Different", this);
    isDifferent->setCheckable(true);
    isDifferent->setChecked(false);
    this->addAction(isDifferent);


    isTangent = new QAction("Tangent", this);
    isTangent->setCheckable(true);
    isTangent->setChecked(false);
    this->addAction(isTangent);


    this->addSeparator();

    deletePoint = new QAction("Delete");
    this->addAction(deletePoint);
}
