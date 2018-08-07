#include <QDebug>
#include "circle.h"

using namespace MoebInv;
using namespace GiNaC;

/*!
 * \brief circle::circle Circle constructor.
 * \param f MoebInv figure.
 * \param p MoebInv cycle to be drawn on the scene.
 * \param l label of the cycle.
 * \param parent
 *
 * Constructs a circle on the scene.
 *
 * Inherits 'graphicCycle'.
 */
circle::circle(MoebInv::figure *f, GiNaC::ex c, QString l) :
    graphicCycle(f, c, l)
{

}

/*!
 * \brief circle::boundingRect Define the bounding rectangle
 * \return QRectF
 *
 * Defines the area on the scene that the object can draw on.
 */
QRectF circle::boundingRect() const{
    return QRectF(
        x - radius,
        y - radius,
        radius * 2,
        radius * 2
    );
}

/*!
 * \brief circle::paint Paint the circle on the scene.
 * \param p QPainter object.
 *
 * This function paints the circle on the scene given various parameters
 * (such as x, y, radius and label). The circle is drawn differently dependent
 * on the drawing metric in use.
 */
void circle::paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *) {

    // check for changes to coordinates
    getParameters();

    // assign brush and pen
    p->setPen(*pen);

    switch (metric) {
        case drawingMetric::ELLIPTIC: {
            // draw circle
            p->drawEllipse(
                QPointF(x, y),
                radius,
                radius
            );

            // add label to side
            p->drawText(x, y + radius - 5, label);

            break;
        }

        case drawingMetric::PARABOLIC: {
            // Reserved for future use
            break;

        }

        case drawingMetric::HYPERBOLIC: {
            // Reserved for future use
            break;
        }
    }
}
