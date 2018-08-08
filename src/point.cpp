#include "point.h"

using namespace GiNaC;
using namespace MoebInv;

/*!
 * \brief point::point Point constructor.
 * \param f MoebInv figure.
 * \param p MoebInv point to be drawn on the scene.
 * \param l label of the point.
 * \param z index in which to draw the object.
 * \param parent
 *
 * Constructs a point on the scene.
 *
 * Inherits 'graphicCycle'.
 */
point::point(MoebInv::figure *f, GiNaC::ex p, QString l, int z) :
    graphicCycle(f, p, l, z)
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
        x - POINT_SIZE,
        y - POINT_SIZE,
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
    switch (METRIC) {
        case drawingMetric::ELLIPTIC: {
            // draw point
            p->drawEllipse(
                x - POINT_SIZE / 2,
                y - POINT_SIZE / 2,
                POINT_SIZE,
                POINT_SIZE
            );

            // add label to side
            p->drawText(x + POINT_SIZE + 3, y + 12, label);

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



