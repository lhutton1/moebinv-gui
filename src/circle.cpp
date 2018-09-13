#include <QDebug>
#include "circle.h"

/*!
 * \brief circle::line Create a new circle.
 * \param struct cycleData data Contains the data needed to draw the circle.
 *
 * Construct a new line on the scene and assign it to the parent graphicCycle.
 */
circle::circle(graphicCycle *parent, struct cycleData data)
{
    this->parent = parent;
    this->scaleFactor = parent->getRelativeScaleFactor();
    this->label = parent->getCycleLabel();

    this->x = data.x;
    this->y = data.y;
    this->radius = data.radius;
    this->pen = data.pen;

    this->setParentItem(parent);
    this->setPos(x, y);

    BOUNDINGRECT_DEBUG = s.value("boundingRectDebug").toBool();
}


/*!
 * \brief circle::paint Paint the circle on the scene.
 * \param painter QPainter object.
 * \param option
 * \param widget
 *
 * This function paints the point on the scene given various parameters
 * (such as x and y). The point is drawn differently dependent
 * on the drawing metric in use.
 */
void circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // assign pen
    painter->setPen(*pen);

    // draw shape based on drawing metric
    switch (s.value("drawingMetric").toInt()) {
        case drawingMetric::ELLIPTIC: {
            QPointF point(0, 0);

            if (BOUNDINGRECT_DEBUG)
                painter->drawRect(this->boundingRect());

            // draw circle
            if (radius < 0)
                return;

            painter->drawEllipse(point, radius, radius);

            // set the painter matrix to correct size for zoom
            painter->setMatrix(parent->stableMatrix(painter->worldMatrix(), point));

            // add label to side
            if (s.value("showLabels").toBool())
                painter->drawText(0, (radius * s.value("initialZoomFactor").toInt() * (*scaleFactor)) - 4, label);

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
 * \brief circle::boundingRect Define the bounding rect.
 * \return QRectF
 *
 * Define the box the object is drawn within on the scene.
 */
QRectF circle::boundingRect() const
{
    return QRectF(
        0 - radius,
        0 - radius,
        radius * 2,
        radius * 2
    );
}


/*!
 * \brief circle::shape Define the clipping mask of the object
 * \return QPainterPath
 *
 * Defines the area in which the shape actually exists.
 */
QPainterPath circle::shape() const
{
    QPointF point(0, 0);
    QPainterPath path;
    QPainterPath subPath;

    path.addEllipse(point, radius, radius);
    subPath.addEllipse(point, radius, radius);

    return path.subtracted(subPath);
}
