#include "cyclecontextmenu.h"

/*!
 * \brief cycleContextMenu::cycleContextMenu Context menu constructor
 *
 * Create a new context menu.
 *      orthogonal
 *      forthogonal
 *      different
 *      tangent
 *      -----------
 *      delete
 */
cycleContextMenu::cycleContextMenu(bool deleteAction)
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

    if (deleteAction) {
        this->addSeparator();

        deletePoint = new QAction("Delete");
        this->addAction(deletePoint);
    }

    // now connect each item to a slot
    // to pass arguments to a slot we need to set up a signal mapper
    QSignalMapper *signalMapper = new QSignalMapper;
    connect(isOrthogonal, SIGNAL(triggered()), signalMapper, SLOT(map()));
    connect(isfOrthogonal, SIGNAL(triggered()), signalMapper, SLOT(map()));
    connect(isDifferent, SIGNAL(triggered()), signalMapper, SLOT(map()));
    connect(isTangent, SIGNAL(triggered()), signalMapper, SLOT(map()));

    signalMapper->setMapping(isOrthogonal, ORTHOGONAL);
    signalMapper->setMapping(isfOrthogonal, FORTHOGONAL);
    signalMapper->setMapping(isDifferent, DIFFERENT);
    signalMapper->setMapping(isTangent, TANGENT);

    // now connect the signal mapper to the function
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(isChecked(int)));

}

void cycleContextMenu::isChecked(int relType) {
    // store a pointer to the relevent menu item
    QPointer<QAction> currentRelation;

    switch (relType) {
        case ORTHOGONAL:
            currentRelation = isOrthogonal;
            break;

        case FORTHOGONAL:
            currentRelation = isfOrthogonal;
            break;

        case DIFFERENT:
            currentRelation = isDifferent;
            break;

        case TANGENT:
            currentRelation = isTangent;
            break;
    }

    // now check whether it needs adding or removing from the list
    if(currentRelation->isChecked()) {
        emit addRelationToList(relType);
    }
    else {
        emit removeRelationFromList();
    }
}
