#include "graphiccycle.h"

graphicCycle::graphicCycle(MoebInv::figure *f, GiNaC::ex c, QString l)
{
    createPointMenu();
    setAcceptHoverEvents(true);
}

/*!
 * \brief point::hoverEnterEvent Mouse enters binding rect of point
 *
 * This event is triggered when the mouse enters the bounding rectangle of the point.
 * The colour of the point is changed to red and a tool tip is set giving information about the point.
 */
void graphicCycle::hoverEnterEvent(QGraphicsSceneHoverEvent *) {
    brush = Qt::red;
    pen.setColor(Qt::red);
    update();

    //set tool tip on hover showing coordinates
    QString toolTipString = "X:" + QString::number(x) + " Y:" + QString::number(y);
    setToolTip(toolTipString);
}

/*!
 * \brief point::hoverLeaveEvent Mouse leaves binding rect of point
 *
 * This event is triggered when the mouse leaves the bounding rectangle of the point.
 * The colour of the point is set back to black, as it is no longer being hovered.
 */
void graphicCycle::hoverLeaveEvent(QGraphicsSceneHoverEvent *) {
    brush = Qt::black;
    pen.setColor(Qt::black);
    update();
}

/*!
 * \brief point::removePoint Remove a point from the scene.
 *
 * Removes a point from the MoebInv figure and then deletes the object removing it from the scene.
 */
void graphicCycle::removePoint()
{
    // remove cycle from moebInv figure
    fig->remove_cycle_node(cycle);
    // emit signal to get cycle removed from the tree
    emit removeFromTree(label);
    // delete object, clearing it from the scene
    delete this;
}

/*!
 * \brief point::contextMenuEvent Menu popup for point
 * \param event
 *
 * Detects when a menu is being requested (i.e. right click) on a point.
 * This gives the use the option to delete the point and see whether it is orthogonal, fOrthogonal, different or tangent.
 */
void graphicCycle::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    menu->popup(event->screenPos());
}

void graphicCycle::isOrthogonalChecked()
{
    if (menu->isOrthogonal->isChecked()) {
        emit addRelationToList(ORTHOGONAL, cycle);
    } else {
        emit removeOrthogonalFromList(cycle);
    }
}

void graphicCycle::isfOrthogonalChecked()
{
    if (menu->isfOrthogonal->isChecked()) {
        emit addRelationToList(FORTHOGONAL, cycle);
    } else {
        emit removeOrthogonalFromList(cycle);
    }
}

void graphicCycle::isDifferentChecked()
{
    if (menu->isDifferent->isChecked()) {
        emit addRelationToList(DIFFERENT, cycle);
    } else {
        emit removeOrthogonalFromList(cycle);
    }
}

void graphicCycle::isTangentChecked()
{
    if (menu->isTangent->isChecked()) {
        emit addRelationToList(TANGENT, cycle);
    } else {
        emit removeOrthogonalFromList(cycle);
    }
}

void graphicCycle::resetRelationalList()
{
    menu->isOrthogonal->setChecked(false);
    menu->isfOrthogonal->setChecked(false);
    menu->isTangent->setChecked(false);
    menu->isDifferent->setChecked(false);
}

QString graphicCycle::getLabel()
{
    return label;
}

/*!
 * \brief createPointMenu Create context menu
 *
 * Create a menu that appears when a point is right clicked.
 */
void graphicCycle::createPointMenu()
{
    menu = new cycleContextMenu;

    connect(menu->isOrthogonal, &QAction::triggered, this, &graphicCycle::isOrthogonalChecked);
    connect(menu->isfOrthogonal, &QAction::triggered, this, &graphicCycle::isfOrthogonalChecked);
    connect(menu->isDifferent, &QAction::triggered, this, &graphicCycle::isDifferentChecked);
    connect(menu->isTangent, &QAction::triggered, this, &graphicCycle::isTangentChecked);
    connect(menu->deletePoint, &QAction::triggered, this, &graphicCycle::removePoint);
}

