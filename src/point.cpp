#include <QDebug>
#include "point.h"

point::point(MoebInv::figure *f, double x, double y, QString label, QGraphicsItem *parent)
{
   fig = f;
   this->x = x;
   this->y = y;
   this->label = label;

   this->setParentItem(parent);

   // create the brush and pen and assign a base colour
   brush = new QBrush(Qt::black);
   pen = new QPen(Qt::black);

   scaleFactor = 1;

}

void point::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // assign brush and pen
    painter->setBrush(*brush);
    painter->setPen(*pen);

    // draw shape
    switch (METRIC) {
        case drawingMetric::ELLIPTIC: {
            QPointF point(x, y);
            painter->setMatrix(stableMatrix(painter->worldMatrix(), point));

            // draw point
            painter->drawEllipse(
                x - POINT_SIZE / 2,
                y - POINT_SIZE / 2,
                POINT_SIZE,
                POINT_SIZE
            );

            // add label to side
            painter->drawText(x + POINT_SIZE + 3, y + 12, label);

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

QRectF point::boundingRect() const
{
    return QRectF(
        x - POINT_SIZE,
        y - POINT_SIZE,
        30 / scaleFactor,
        30 / scaleFactor
    );
}

/*!
 * \brief graphicCycle::stableMatrix create new transformation matrix
 * \param matrix the current transformation matrix
 * \param p point at which the transformation is centered
 * \return QMatrix - the new transformation matrix
 *
 * Create a new matrix which will keep items the same size when the zoom transformation is applied to it.
 */
QMatrix point::stableMatrix(const QMatrix &matrix, const QPointF &p)
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
