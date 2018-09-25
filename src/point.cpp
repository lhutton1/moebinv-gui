#include <QDebug>
#include "point.h"

/*!
 * \brief point::point Create a new point.
 * \param struct cycleData data Contains the data needed to draw the point.
 *
 * Construct a new point on the scene and assign it to the parent graphicCycle.
 */
point::point(graphicCycle *parent, struct cycleData data)
{
    this->parent = parent;
    this->scaleFactor = parent->getRelativeScaleFactor();
    this->label = parent->getCycleLabel();

    this->x = data.x;
    this->y = data.y;
    this->brush = data.brush;
    this->pen = data.pen;

    this->setParentItem(parent);
    this->setPos(x, y);

    // override normal pen width
    this->pen->setWidth(1);

    BOUNDINGRECT_DEBUG = s.value("boundingRectDebug").toBool();
}


/*!
 * \brief point::paint Paint the point on the scene.
 * \param painter QPainter object.
 * \param option
 * \param widget
 *
 * This function paints the circle on the scene given various parameters
 * (such as x and y). The circle is drawn differently dependent
 * on the drawing metric in use.
 */
void point::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    const double POINT_SIZE = s.value("pointSize").toDouble();

    // assign brush and pen to the painter.
    painter->setPen(*pen);
    painter->setBrush(*brush);

    // draw shape
    switch (s.value("pointMetric").toInt()) {
        case drawingMetric::ELLIPTIC: {
            if (BOUNDINGRECT_DEBUG)
                painter->drawRect(this->boundingRect());

            // set the painter matrix to correct size for zoom
            painter->setMatrix(parent->stableMatrix(painter->worldMatrix(), QPointF(0, 0)));

            // draw point
            painter->drawEllipse(
                0 - POINT_SIZE / 2,
                0 - POINT_SIZE / 2,
                POINT_SIZE,
                POINT_SIZE
            );

            // add label to side
            if (s.value("showLabels").toBool())
                painter->drawText(POINT_SIZE + 3, 12, label);

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
 * \brief point::boundingRect Define the bounding rect.
 * \return QRectF
 *
 * Define the box the object is drawn within on the scene.
 */
QRectF point::boundingRect() const
{
    int labelWidth = (label.count() * 6 + 10);
    double sf = s.value("initialZoomFactor").toInt() * (*scaleFactor);

    QPointF topLeft = QPointF(0 / sf, -15 / sf);
    QPointF bottomRight = QPointF(labelWidth / sf, 0 / sf);

    return QRectF (topLeft, bottomRight);
}
