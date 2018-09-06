#include <QDebug>
#include "point.h"

/*!
 * \brief point::point Create a new point.
 * \param struct cycleData data Contains the data needed to draw the point.
 *
 * Construct a new point on the scene and assign it to the parent graphicCycle.
 */
point::point(double *relativeScaleFactor, struct cycleData data)
{
   this->scaleFactor = relativeScaleFactor;

   this->x = data.x;
   this->y = data.y;
   this->label = data.label;
   this->brush = data.brush;
   this->pen = data.pen;

   this->setParentItem(data.cycle);
   this->setPos(x, y);

   BOUNDINGRECT_DEBUG = false;
}


/*!
 * \brief point::paint Paint the point on the scene.
 * \param p QPainter object.
 *
 * This function paints the point on the scene given various parameters
 * (such as x and y). The point is drawn differently dependent
 * on the drawing metric in use.
 */
void point::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    const double POINT_SIZE = s.value("pointSize").toDouble();

    // assign brush and pen to the painter.
    painter->setPen(*pen);
    painter->setBrush(*brush);

    // draw shape
    switch (s.value("drawingMetric").toInt()) {
        case drawingMetric::ELLIPTIC: {
            if (BOUNDINGRECT_DEBUG)
                painter->drawRect(this->boundingRect());

            // set the painter matrix to correct size for zoom
            painter->setMatrix(stableMatrix(painter->worldMatrix(), QPointF(0, 0)));

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

    QPointF topLeft = QPointF(0 / *scaleFactor, -15 / *scaleFactor);
    QPointF bottomRight = QPointF(labelWidth / *scaleFactor, 0 / *scaleFactor);

    return QRectF (topLeft, bottomRight);
}


/*!
 * \brief point::stableMatrix create new transformation matrix
 * \param matrix the current transformation matrix
 * \param p point at which the transformation is centered
 * \return QMatrix - the new transformation matrix
 *
 * Create a new matrix which will keep items the same size when the zoom transformation is applied to it.
 */
QMatrix point::stableMatrix(const QMatrix &matrix, const QPointF &p) const
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
