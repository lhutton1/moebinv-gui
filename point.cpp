#include <QDebug>
#include <iostream>
#include <string>
#include "point.h"

using namespace GiNaC;
using namespace MoebInv;

/*!
 * \brief point::point Point constructor.
 * \param f MoebInv figure.
 * \param p MoebInv point to be drawn on the scene.
 * \param l label of the point.
 * \param parent
 *
 * Constructs a point on the scene by implementing a QGraphicsItem.
 */
point::point(figure *f, ex p, QString l, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    brush(Qt::black),
    pen(Qt::black)
{
    radius = 2.5;
    cycle = p;
    fig = f;
    label = l;

    getParameters();
    setAcceptHoverEvents(true);
}

/*!
 * \brief point::hoverEnterEvent
 */
void point::hoverEnterEvent(QGraphicsSceneHoverEvent *) {
    brush = Qt::red;
    pen.setColor(Qt::red);
    update();

    //set tool tip when hover
    QString toolTipString = "X:" + QString::number(x) + " Y:" + QString::number(y);
    setToolTip(toolTipString);
}

/*!
 * \brief point::hoverLeaveEvent
 */
void point::hoverLeaveEvent(QGraphicsSceneHoverEvent *) {
    brush = Qt::black;
    pen.setColor(Qt::black);
    update();
}

void point::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu *menu = new QMenu;

    isOrthagonal = new QAction("Orthagonal");
    isOrthagonal->setCheckable(true);
    isOrthagonal->setChecked(true);
    menu->addAction(isOrthagonal);
    //CONNECT....

    isfOrthagonal = new QAction("F-Orthagonal");
    isfOrthagonal->setCheckable(true);
    isfOrthagonal->setChecked(true);
    menu->addAction(isfOrthagonal);
    //CONNECT....

    isDifferent = new QAction("Different");
    isDifferent->setCheckable(true);
    isDifferent->setChecked(true);
    menu->addAction(isDifferent);
    //CONNECT....

    isTangent = new QAction("Tangent");
    isTangent->setCheckable(true);
    isTangent->setChecked(true);
    menu->addAction(isTangent);
    //CONNECT....

    menu->addSeparator();

    menu->addAction("Delete");
    //CONNECT....

    menu->popup(event->screenPos());
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
 * \brief point::paint
 * \param p
 */
void point::paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *) {
    getParameters();
    p->setPen(pen);
    p->setBrush(brush);

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
 * \brief point::getParameters
 */
void point::getParameters() {
    // get cycle that has just been added
    cycle2D c = ex_to<cycle2D>(fig->get_cycle(cycle)[0]);

    // now break into components
    x = ex_to<numeric>(c.center()[0]).to_double();
    y = ex_to<numeric>(c.center()[1]).to_double();
}

//void ex_to_string(const ex & E)
//{
//    std::ostringstream drawing;
//    drawing << E;
//    string dr = drawing.str().c_str();

//    QString drw = QString::fromStdString(dr);
//    qDebug() << drw;
//}



