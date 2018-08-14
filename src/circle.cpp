#include <QDebug>
#include "circle.h"

circle::circle(MoebInv::figure *f, double x, double y, double radius, QString label, QGraphicsItem *parent, double *relativeScaleFactor)
{
   fig = f;
   this->x = x;
   this->y = y;
   this->radius = radius;
   this->label = label;
   this->relativeScaleFactor = relativeScaleFactor;

   this->setParentItem(parent);

   // create the brush and pen and assign a base colour
   brush = new QBrush(Qt::black);
   pen = new QPen(Qt::black);
}

void circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // assign brush and pen
    pen->setCosmetic(true);
    pen->setWidth(LINE_WIDTH);
    painter->setPen(*pen);

    switch (METRIC) {
        case drawingMetric::ELLIPTIC: {
            // draw circle
            painter->drawEllipse(
                QPointF(x, y),
                radius,
                radius
            );

            QPointF point(x, y);
            painter->setMatrix(stableMatrix(painter->worldMatrix(), point));

            // add label to side
            painter->drawText(x, y + (*relativeScaleFactor) * radius - 4, label);

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
QPainterPath circle::shape() const
{
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
