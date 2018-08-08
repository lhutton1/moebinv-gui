#include <QDebug>
#include "graphiccycle.h"

using namespace GiNaC;
using namespace MoebInv;

/*!
 * \brief graphicCycle::graphicCycle
 * \param f Moebinv figure provides access to the cycle data stored in the library.
 * \param c The cycle that has just been created and added to the figure.
 * \param l The label used by the cycle as a unique identifier.
 */
graphicCycle::graphicCycle(figure *f, ex c, QString l, int z)
{
    // assign parameters
    fig = f;
    cycle = c;
    label = l;
    zIndex = z;

    // set zIndex to draw item
    this->setZValue(zIndex);

    // create the brush and pen and assign a base colour
    brush = new QBrush(Qt::black);
    pen = new QPen(Qt::black);

    // create a new menu to be used when the user right clicks on the object
    menu = new cycleContextMenu;

    // to pass arguments to a slot we need to set up a signal mapper
    QSignalMapper *signalMapper = new QSignalMapper;
    connect(menu->isOrthogonal, SIGNAL(triggered()), signalMapper, SLOT(map()));
    connect(menu->isfOrthogonal, SIGNAL(triggered()), signalMapper, SLOT(map()));
    connect(menu->isDifferent, SIGNAL(triggered()), signalMapper, SLOT(map()));
    connect(menu->isTangent, SIGNAL(triggered()), signalMapper, SLOT(map()));

    signalMapper->setMapping(menu->isOrthogonal, ORTHOGONAL);
    signalMapper->setMapping(menu->isfOrthogonal, FORTHOGONAL);
    signalMapper->setMapping(menu->isDifferent, DIFFERENT);
    signalMapper->setMapping(menu->isTangent, TANGENT);

    // now connect the signal mapper to the function
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(isChecked(int)));

    // add deletepoint connection
    connect(menu->deletePoint, &QAction::triggered, this, &graphicCycle::removeCycle);

    // allow hover events to take place, used to highlight
    // currently hovered object on the scene
    setAcceptHoverEvents(true);

    // get parameters to draw the cycle
    getParameters();
}

/*!
 * \brief graphicCycle::hoverEnterEvent Mouse enters clipping mask of point.
 *
 * This event is triggered when the mouse enters the clipping mask of the point.
 * The colour of the point is changed to red and a tool tip is set giving information about the point.
 */
void graphicCycle::hoverEnterEvent(QGraphicsSceneHoverEvent *) {
    // set colour to red
    brush->setColor(Qt::red);
    pen->setColor(Qt::red);
    update();

    //set tool tip on hover showing coordinates
    QString toolTipString = "X:" + QString::number(x) + " Y:" + QString::number(y);
    setToolTip(toolTipString);
}

/*!
 * \brief graphicCycle::hoverLeaveEvent Mouse leaves clipping mask of point.
 *
 * This event is triggered when the mouse leaves the clipping mask of the point.
 * The colour of the point is set back to black, as it is no longer being hovered.
 */
void graphicCycle::hoverLeaveEvent(QGraphicsSceneHoverEvent *) {
    // set colour to black
    brush->setColor(Qt::black);
    pen->setColor(Qt::black);
    update();
}

/*!
 * \brief graphicCycle::removeCycle Remove a cycle from the scene.
 *
 * Removes a cycle from the MoebInv figure and then deletes the object removing it from the scene.
 */
void graphicCycle::removeCycle()
{
    // remove cycle from moebInv figure
    fig->remove_cycle_node(cycle);

    // emit signal to get cycle removed from the tree
    emit removeFromTree(label);

    // delete object, clearing it from the scene
    delete this;
}

/*!
 * \brief graphicCycle::contextMenuEvent Menu popup for cycle.
 * \param event new mouse event.
 *
 * Detects when a menu is being requested (i.e. right click) on a cycle.
 * This gives the user the option to delete the point and set relevent relations.
 */
void graphicCycle::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    menu->popup(event->screenPos());
}

/*!
 * \brief graphicCycle::isChecked Check if relation needs adding to list.
 * \param relType The relation type e.g. orthogonal, forthogonal, different or tangent.
 *
 * Checks whether the specific relation is checked. If it is it adds it to the list.
 * If not it removes it from the list.
 */
void graphicCycle::isChecked(int relType)
{
    // store a pointer to the relevent menu item
    QPointer<QAction> currentRelation;

    switch (relType) {
        case ORTHOGONAL:
            currentRelation = menu->isOrthogonal;
            break;

        case FORTHOGONAL:
            currentRelation = menu->isfOrthogonal;
            break;

        case DIFFERENT:
            currentRelation = menu->isDifferent;
            break;

        case TANGENT:
            currentRelation = menu->isTangent;
            break;
    }

    // now check whether it needs adding or removing from the list
    if(currentRelation->isChecked())
        emit addRelationToList(relType, cycle);
    else
        emit removeRelationFromList(cycle);

}

/*!
 * \brief graphicCycle::resetRelationalList Uncheck all relations from menu.
 */
void graphicCycle::resetRelationalList()
{
    menu->isOrthogonal->setChecked(false);
    menu->isfOrthogonal->setChecked(false);
    menu->isTangent->setChecked(false);
    menu->isDifferent->setChecked(false);
}

/*!
 * \brief graphicCycle::getLabel Getter function for label.
 * \return Label.
 */
QString graphicCycle::getLabel()
{
    return label;
}

/*!
 * \brief graphicsCycle::getParameters get x and y coordinates.
 *
 * Get the x and y coordinates of the point from the cycle in the figure.
 */
void graphicCycle::getParameters() {
    // get cycle that has just been added
    cycle2D c = ex_to<cycle2D>(fig->get_cycle(cycle)[0]);

    // now break into components
    x = ex_to<numeric>(c.center()[0]).to_double();
    y = ex_to<numeric>(c.center()[1]).to_double();
    radius = qSqrt(ex_to<numeric>(c.radius_sq()).to_double());
}

