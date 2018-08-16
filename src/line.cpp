#include <QDebug>
#include "line.h"

line::line(struct cycleData data)
{
   fig = data.fig;
   this->x = data.x;
   this->y = data.y;
   this->label = data.label;

   this->setParentItem(data.cycle);

   // create the brush and pen and assign a base colour
   brush = data.brush;
   pen = data.pen;

   setAcceptHoverEvents(true);

   // break line equation into 2 distinct points, given by x1, x2, y1, and y2.
   x1 = (y * -(SCENE_SIZE)) + c;

   if (x != 0)
       x1 /= x;

   x2 = (y * SCENE_SIZE) + c;

   if (x != 0)
        x2 /= x;

   y1 = (x * -(SCENE_SIZE)) + c;

   if (y != 0)
       y1 /= y;

   y2 = (x * SCENE_SIZE) + c;

   if (y != 0)
       y2 /= y;

}

void line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // assign brush and pen
        painter->setBrush(*brush);
        painter->setPen(*pen);

        pen->setCosmetic(true);
        pen->setWidth(LINE_WIDTH);

        // draw shape
        switch (METRIC) {
            case drawingMetric::ELLIPTIC: {
                // draw line
                painter->drawLine(x1, y1, x2, y2);

                QPointF point(x, y);
                painter->setMatrix(stableMatrix(painter->worldMatrix(), point));

                // add label to side
                painter->drawText(x, y - 5, label);

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

QRectF line::boundingRect() const
{
    int padding;

    // if padding is less than 15 the label won't be visible
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
 * \brief graphicCycle::stableMatrix create new transformation matrix
 * \param matrix the current transformation matrix
 * \param p point at which the transformation is centered
 * \return QMatrix - the new transformation matrix
 *
 * Create a new matrix which will keep items the same size when the zoom transformation is applied to it.
 */
QMatrix line::stableMatrix(const QMatrix &matrix, const QPointF &p)
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

void line::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    emit isHovered();
}

void line::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    emit isUnHovered();
}

