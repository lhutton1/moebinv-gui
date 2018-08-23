#include <QDebug>
#include "circle.h"

circle::circle(struct cycleData data)
{
   fig = data.fig;
   this->x = data.x;
   this->y = data.y;
   this->radius = data.radius;
   this->label = data.label;
   this->relativeScaleFactor = data.relativeScaleFactor;

   this->setParentItem(data.cycle);

   // create the brush and pen and assign a base colour
   brush = data.brush;
   pen = data.pen;

   setAcceptHoverEvents(true);
   setPos(x, y);

   BOUNDINGRECT_DEBUG = false;
}

void circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // assign brush and pen
    pen->setCosmetic(true);
    pen->setWidth(LINE_WIDTH);
    painter->setPen(*pen);

    switch (METRIC) {
        case drawingMetric::ELLIPTIC: {
            if (BOUNDINGRECT_DEBUG)
                painter->drawRect(this->boundingRect());

            // draw circle
            painter->drawEllipse(
                QPointF(0, 0),
                radius,
                radius
            );

            QPointF point(0, 0);
            painter->setMatrix(stableMatrix(painter->worldMatrix(), point));

            // add label to side
            if (s.value("showLabels").toBool())
                painter->drawText(0, 0 + (*relativeScaleFactor) * radius - 4, label);

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

QRectF circle::boundingRect() const
{
    return QRectF(
        0 - radius - LINE_HOVER_PADDING,
        0 - radius - LINE_HOVER_PADDING,
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
QPainterPath circle::shape() const
{
    QPainterPath path;
    QPainterPath subPath;

    path.addEllipse(
        QPointF(0 - LINE_HOVER_PADDING, 0 - LINE_HOVER_PADDING),
        radius + LINE_HOVER_PADDING * 2,
        radius + LINE_HOVER_PADDING * 2
    );

    subPath.addEllipse(
        QPointF(0 + LINE_HOVER_PADDING, 0 + LINE_HOVER_PADDING),
        radius - LINE_HOVER_PADDING * 2,
        radius - LINE_HOVER_PADDING * 2
    );

    return path.subtracted(subPath);
}

/*!
 * \brief graphicCycle::stableMatrix create new transformation matrix
 * \param matrix the current transformation matrix
 * \param p point at which the transformation is centered
 * \return QMatrix - the new transformation matrix
 *
 * Create a new matrix which will keep items the same size when the zoom transformation is applied to it.
 */
QMatrix circle::stableMatrix(const QMatrix &matrix, const QPointF &p)
{
    QMatrix newMatrix = matrix;

    qreal scaleX, scaleY;
    scaleX = newMatrix.m11();
    scaleY = newMatrix.m22();
    newMatrix.scale(1.0/scaleX, 1.0/scaleY);

    qreal offsetX, offsetY;
    offsetX = p.x() * (scaleX - 1.0);
    offsetY = p.y() * (scaleY - 1.0);
    newMatrix.translate(offsetX, offsetY);

    return newMatrix;
}

void circle::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    emit isHovered();
}

void circle::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    emit isUnHovered();
}
