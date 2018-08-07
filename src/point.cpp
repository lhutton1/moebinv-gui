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
 * Constructs a point on the scene.
 *
 * Inherits 'graphicCycle'.
 */
point::point(MoebInv::figure *f, GiNaC::ex p, QString l) :
    graphicCycle(f, p, l),
    DRAWING_RADIUS(4)
{

}

/*!
 * \brief point::boundingRect Define the bounding rectangle
 * \return QRectF
 *
 * Defines the area on the scene that the object can draw on.
 */
QRectF point::boundingRect() const
{
    return QRectF(
        x - DRAWING_RADIUS,
        y - DRAWING_RADIUS,
        30,
        30
    );
}

/*!
 * \brief point::paint Paint the point on the scene.
 * \param p QPainter object.
 *
 * This function paints the point on the scene given various parameters
 * (such as x, y, radius and label). The point is drawn differently dependent
 * on the drawing metric in use.
 */
void point::paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *)
{
    // check for changes to coordinates
    getParameters();

    // assign brush and pen
    p->setBrush(*brush);
    p->setPen(*pen);

    // draw shape
    switch (metric) {
        case drawingMetric::ELLIPTIC: {
            // draw point
            p->drawEllipse(
                x - DRAWING_RADIUS / 2,
                y - DRAWING_RADIUS / 2,
                DRAWING_RADIUS,
                DRAWING_RADIUS
            );

            // add label to side
            p->drawText(x + DRAWING_RADIUS + 3, y + 12, label);

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



