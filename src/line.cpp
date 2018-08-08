#include <QDebug>
#include "line.h"

using namespace GiNaC;
using namespace MoebInv;

/*!
 * \brief line::line Line constructor.
 * \param f MoebInv figure.
 * \param p MoebInv line to be drawn on the scene.
 * \param l label of the line.
 * \param z index in which to draw the object.
 * \param parent
 *
 * Constructs a line on the scene.
 *
 * Inherits 'graphicCycle'.
 */
line::line(MoebInv::figure *f, GiNaC::ex p, QString l, int z) :
    graphicCycle(f, p, l, z)
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
    int padding;

    LINE_HOVER_PADDING < 15 ?
        padding = 15 :
        padding = LINE_HOVER_PADDING;

    return QRectF(
        x1 - padding,
        y1 - padding,
        abs(x1 - x2) + padding * 2,
        abs(y1 - y2) + padding * 2
    );
}

/*!
 * \brief circle::shape Define the clipping mask of the object
 * \return QPainterPath
 *
 * Defines the area in which hover events take place.
 */
QPainterPath line::shape() const {
    QPainterPath path;

    path.addRect(
        x1 - LINE_HOVER_PADDING,
        y1 - LINE_HOVER_PADDING,
        abs(x1 - x2) + LINE_HOVER_PADDING * 2,
        abs(y1 - y2) + LINE_HOVER_PADDING * 2
    );

    return path;
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
    switch (METRIC) {
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

    x1 = (y * -(SCENE_SIZE));

    if (x != 0)
        x1 /= x;

    x2 = (y * SCENE_SIZE);

    if (x != 0)
         x2 /= x;

    y1 = (x * -(SCENE_SIZE));

    if (y != 0)
        y1 /= y;

    y2 = (x * SCENE_SIZE);

    if (y != 0)
        y2 /= y;
}
