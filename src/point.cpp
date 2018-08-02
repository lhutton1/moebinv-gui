#include <QDebug>
#include <string>
#include <iostream>
#include "point.h"

using namespace GiNaC;
using namespace MoebInv;

void ex_to_string(const ex & E)
{
    std::ostringstream drawing;
    drawing << E;
    string dr = drawing.str().c_str();

    QString drw = QString::fromStdString(dr);
    qDebug() << drw;
}

/*!
 * \brief point::point Point constructor.
 * \param f MoebInv figure.
 * \param p MoebInv point to be drawn on the scene.
 * \param l label of the point.
 * \param parent
 *
 * Constructs a point on the scene by implementing a QGraphicsItem.
 */
point::point(MoebInv::figure *f, GiNaC::ex p, QString l) :
    brush(Qt::black),
    pen(Qt::black)
{
    radius = 2.5;
    cycle = p;
    fig = f;
    label = l;

    getParameters();
    createPointMenu();
    setAcceptHoverEvents(true);
}

/*!
 * \brief point::hoverEnterEvent Mouse enters binding rect of point
 *
 * This event is triggered when the mouse enters the bounding rectangle of the point.
 * The colour of the point is changed to red and a tool tip is set giving information about the point.
 */
void point::hoverEnterEvent(QGraphicsSceneHoverEvent *) {
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
void point::hoverLeaveEvent(QGraphicsSceneHoverEvent *) {
    brush = Qt::black;
    pen.setColor(Qt::black);
    update();
}

/*!
 * \brief point::boundingRect
 * \return
 */
QRectF point::boundingRect() const{
    return QRectF(
        x - radius,
        y - radius,
        30,
        30
    );
}

/*!
 * \brief point::paint Paint the point on the scene.
 * \param p
 *
 * This function paints the point on the scene given various parameters
 * (such as x, y, radius and label). The point is drawn differently dependent
 * on the drawing metric in use.
 */
void point::paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *) {
    getParameters();
    p->setBrush(brush);
    p->setPen(pen);

    switch (metric) {
        case drawingMetric::ELLIPTIC: {
            // draw point
            p->drawEllipse(
                x - radius / 2,
                y - radius / 2,
                radius,
                radius
            );

            // add label to side
            p->drawText(x + radius + 3, y + 12, label);

            break;
        } case drawingMetric::PARABOLIC: {
            // Reserved for future use
            break;

        } case drawingMetric::HYPERBOLIC: {
            // Reserved for future use
            break;
        }
    }
}

/*!
 * \brief point::getParameters get x and y coordinates
 *
 * Get the x and y coordinates of the point from the cycle in the figure.
 */
void point::getParameters() {
    // get cycle that has just been added
    cycle2D c = ex_to<cycle2D>(fig->get_cycle(cycle)[0]);

    // now break into components
    x = ex_to<numeric>(c.center()[0]).to_double();
    y = ex_to<numeric>(c.center()[1]).to_double();
}

/*!
 * \brief point::removePoint Remove a point from the scene.
 *
 * Removes a point from the MoebInv figure and then deletes the object removing it from the scene.
 */
void point::removePoint()
{
    // remove cycle from moebInv figure
    fig->remove_cycle_node(cycle);
    // emit signal to get cycle removed from the tree
    emit removeFromTree(label);
    // delete object, clearing it from the scene
    delete this;
}

/*!
 * \brief createPointMenu Create context menu
 *
 * Create a menu that appears when a point is right clicked.
 */
void point::createPointMenu()
{
    menu = new QMenu;

    isOrthagonal = new QAction("Orthagonal", this);
    isOrthagonal->setCheckable(true);
    isOrthagonal->setChecked(false);
    menu->addAction(isOrthagonal);
    //connect(isOrthagonal, &QAction::triggered, this, &point::changeToChecked);

    isfOrthagonal = new QAction("F-Orthagonal", this);
    isfOrthagonal->setCheckable(true);
    isfOrthagonal->setChecked(false);
    menu->addAction(isfOrthagonal);
    //connect(isfOrthagonal, &QAction::triggered, this, &point::changeToChecked);

    isDifferent = new QAction("Different", this);
    isDifferent->setCheckable(true);
    isDifferent->setChecked(false);
    menu->addAction(isDifferent);
    //connect(isDifferent, &QAction::triggered, this, &point::changeToChecked);

    isTangent = new QAction("Tangent", this);
    isTangent->setCheckable(true);
    isTangent->setChecked(false);
    menu->addAction(isTangent);
    //connect(isTangent, &QAction::triggered, this, &point::changeToChecked);

    menu->addSeparator();

    deletePoint = new QAction("Delete");
    menu->addAction(deletePoint);
    connect(deletePoint, &QAction::triggered, this, &point::removePoint);
}

/*!
 * \brief point::contextMenuEvent Menu popup for point
 * \param event
 *
 * Detects when a menu is being requested (i.e. right click) on a point.
 * This gives the use the option to delete the point and see whether it is orthagonal, fOrthagonal, different or tangent.
 */
void point::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    menu->popup(event->screenPos());
}




