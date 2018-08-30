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


cycleContextMenu::cycleContextMenu(bool deleteAction, QObject *parent)
{
    // Orthogonal
    isOrthogonal = new QAction("Orthogonal", this);
    isOrthogonal->setCheckable(true);
    isOrthogonal->setChecked(false);
    this->addAction(isOrthogonal);

    // F-Orthogonal
    isfOrthogonal = new QAction("F-Orthogonal", this);
    isfOrthogonal->setCheckable(true);
    isfOrthogonal->setChecked(false);
    this->addAction(isfOrthogonal);

    // Different
    isDifferent = new QAction("Different", this);
    isDifferent->setCheckable(true);
    isDifferent->setChecked(false);
    this->addAction(isDifferent);

    // A-Different
    isADifferent = new QAction("A Different", this);
    isADifferent->setCheckable(true);
    isADifferent->setChecked(false);
    this->addAction(isADifferent);

    this->addSeparator();

    // Tangent
    isTangent = new QAction("Tangent (radio)", this);
    isTangent->setCheckable(true);
    isTangent->setChecked(false);
    this->addAction(isTangent);

    // Tangent I
    isTangent_i = new QAction("Tangent I (radio)", this);
    isTangent_i->setCheckable(true);
    isTangent_i->setChecked(false);
    this->addAction(isTangent_i);

    // Tangent O
    isTangent_o = new QAction("Tangent O (radio)", this);
    isTangent_o->setCheckable(true);
    isTangent_o->setChecked(false);
    this->addAction(isTangent_o);

    this->addSeparator();

    // Steiner Power
    steinerPower = new QAction("Steiner Power...", this);
    steinerPower->setCheckable(true);
    steinerPower->setChecked(false);
    this->addAction(steinerPower);

    // Cycle Angle
    cycleAngle = new QAction("Cycle Angle...", this);
    cycleAngle->setCheckable(true);
    cycleAngle->setChecked(false);
    this->addAction(cycleAngle);

    // Cycle Cross T Distance
    cycleCrossTDistance = new QAction("Cycle Cross T Distance...", this);
    cycleCrossTDistance->setCheckable(true);
    cycleCrossTDistance->setChecked(false);
    this->addAction(cycleCrossTDistance);

    // Product Sign
    productSign = new QAction("Product Sign...", this);
    productSign->setCheckable(true);
    productSign->setChecked(false);
    this->addAction(productSign);

    // Cycle Mobius
    cycleMobius = new QAction("Cycle Mobius...", this);
    cycleMobius->setCheckable(true);
    cycleMobius->setChecked(false);
    this->addAction(cycleMobius);

    // Cycle Sl2
    cycleSl2 = new QAction("Cycle Sl2...", this);
    cycleSl2->setCheckable(true);
    cycleSl2->setChecked(false);
    this->addAction(cycleSl2);

    this->addSeparator();

    // Change colour option
    changeColour = new QAction("Change Colour...", this);
    this->addAction(changeColour);

    // Loop through items that have been added

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

/*!
 * \brief cycleContextMenu::isChecked
 * \param relType the type of relation that has been checked
 *
 * This functions checks whether the menu item of the 'relType' relation
 * has been checked or unchecked. If it has been checked the cycle is added to the list,
 * if it has been unchecked the cycle is removed from the list.
 */
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
        emit removeRelationFromList(relType);
    }
}
