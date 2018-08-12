#include <QDebug>
#include "circle.h"

using namespace MoebInv;
using namespace GiNaC;

/*!
 * \brief circle::circle Circle constructor.
 * \param f MoebInv figure.
 * \param p MoebInv cycle to be drawn on the scene.
 * \param l label of the cycle.
 * \param z index in which to draw the object.
 * \param parent
 *
 * Constructs a circle on the scene.
 *
 * Inherits 'graphicCycle'.
 */
circle::circle(MoebInv::figure *f, GiNaC::ex c, QString l, int z) :
    graphicCycle(f, c, l, z)
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
        x - radius - LINE_HOVER_PADDING,
        y - radius - LINE_HOVER_PADDING,
        radius * 2 + LINE_HOVER_PADDING * 2,
        radius * 2 + LINE_HOVER_PADDING * 2
    );
}

/*!
 * \brief circle::shape Define the clipping mask of the object
 * \return QPainterPath
 *
 * Defines the area in which hover events take place.
 */
QPainterPath circle::shape() const {
    QPainterPath path;
    QPainterPath subPath;

    path.addEllipse(
        QPointF(x - LINE_HOVER_PADDING, y - LINE_HOVER_PADDING),
        radius + LINE_HOVER_PADDING * 2,
        radius + LINE_HOVER_PADDING * 2
    );

    subPath.addEllipse(
        QPointF(x + LINE_HOVER_PADDING, y + LINE_HOVER_PADDING),
        radius - LINE_HOVER_PADDING * 2,
        radius - LINE_HOVER_PADDING * 2
    );

    return path.subtracted(subPath);
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
    pen->setCosmetic(true);
    pen->setWidth(LINE_WIDTH);
    p->setPen(*pen);

    switch (METRIC) {
        case drawingMetric::ELLIPTIC: {
            // draw circle
            p->drawEllipse(
                QPointF(x, y),
                radius,
                radius
            );

            QPointF point(x, y);
            p->setMatrix(stableMatrix(p->worldMatrix(), point));

            // add label to side
            p->drawText(x, y + radius * scaleFactor - 4, label);

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
