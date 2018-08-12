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

    // connect signals
    connect(menu, &cycleContextMenu::addRelationToList, this, &graphicCycle::addToList);
    connect(menu, &cycleContextMenu::removeRelationFromList, this, &graphicCycle::removeFromList);
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
    // emit signal to get cycle removed from the tree
    emit removeFromTree(this);

    // remove cycle from moebInv figure
    fig->remove_cycle_node(cycle);

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
 * \return QString.
 */
QString graphicCycle::getLabel()
{
    return label;
}

/*!
 * \brief graphicCycle::getCycle Getter function for cycle.
 * \return ex.
 */
ex graphicCycle::getCycle()
{
    return cycle;
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
    x = ex_to<numeric>(c.center().op(0)).to_double();
    y = ex_to<numeric>(c.center().op(1)).to_double();
    radius = qSqrt(ex_to<numeric>(c.radius_sq()).to_double());
}

/*!
 * \brief graphicCycle::addToList
 * \param relType
 *
 * Slot to add a certain cycle to the list. Emmits a signal to call slot
 * in MainWindow to add the cycle to the list.
 */
void graphicCycle::addToList(int relType)
{
    emit addRelationToList(relType, cycle);
}

/*!
 * \brief graphicCycle::removeFromList
 *
 * Slot to remove cycle from list. Emmits a signal to call slot in
 * MainWindow to remove the cycle from the list.
 */
void graphicCycle::removeFromList()
{
    emit removeRelationFromList(cycle);
}

QMatrix graphicCycle::stableMatrix(const QMatrix &matrix, const QPointF &p)
{
    QMatrix newMatrix = matrix;

    qreal scaleX, scaleY;
    scaleX = newMatrix.m11();
    scaleY = newMatrix.m22();
    newMatrix.scale(1.0/scaleX, 1.0/scaleY);

    qreal offsetX, offsetY;
    offsetX = p.x()*(scaleX-1.0);
    offsetY = p.y()*(scaleY-1.0);
    newMatrix.translate(offsetX, offsetY);

    return newMatrix;
}

void graphicCycle::setScaleFactor(double sf)
{
    scaleFactor = sf;
}

