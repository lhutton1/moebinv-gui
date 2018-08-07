#include <QDebug>
#include "line.h"

using namespace GiNaC;
using namespace MoebInv;

/*!
 * \brief line::line Line constructor.
 * \param f MoebInv figure.
 * \param p MoebInv line to be drawn on the scene.
 * \param l label of the line.
 * \param parent
 *
 * Constructs a line on the scene.
 *
 * Inherits 'graphicCycle'.
 */
line::line(MoebInv::figure *f, GiNaC::ex p, QString l) :
    graphicCycle(f, p, l)
{
    getParameters();
}

/*!
 * \brief line::boundingRect Define the bounding rectangle
 * \return QRectF
 *
 * Defines the area on the scene that the object can draw on.
 */
QRectF line::boundingRect() const
{
    return QRectF(
        x,
        y,
        30,
        30
    );
}

/*!
 * \brief line::paint Paint the line on the scene.
 * \param p QPainter object.
 *
 * This function paints the line on the scene given various parameters
 * (such as x, y, radius and label). The line is drawn differently dependent
 * on the drawing metric in use.
 */
void line::paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *)
{
    // check for changes to coordinates
    getParameters();

    // assign brush and pen
    p->setBrush(*brush);
    p->setPen(*pen);

    // draw shape
    switch (metric) {
        case drawingMetric::ELLIPTIC: {
            // draw line
            p->drawLine(x1, y1, x2, y2);

            // add label to side
            p->drawText(x, y - 5, label);

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

/*!
 * \brief graphicsCycle::getParameters get x and y coordinates.
 *
 * Get the x and y coordinates of the point from the line in the figure.
 */
void line::getParameters() {
    // get cycle that has just been added
    cycle2D c = ex_to<cycle2D>(fig->get_cycle(cycle)[0]);

    // now break into components
    x = ex_to<numeric>(c.get_l(0).evalf()).to_double();
    y = ex_to<numeric>(c.get_l(1).evalf()).to_double();
    double a = ex_to<numeric>((c.get_m()/2).evalf()).to_double();

    qDebug() << x << y;

    x1 = (y * -520);

    if (x != 0)
        x1 /= x;

    x2 = (y * 520);

    if (x != 0)
         x2 /= x;

    y1 = (x * -520);

    if (y != 0)
        y1 /= y;

    y2 = (x * 520);

    if (y != 0)
        y2 /= y;

    qDebug() << x1 << x2 << y1 << y2;


}
