#include <QDebug>
#include "point.h"

/*!
 * \brief point::point Create a new point.
 * \param f the figure.
 * \param x the x coordinate the point needs to be placed at.
 * \param y the y coordinate the point needs to be placed at.
 * \param label the label to be displayed.
 * \param parent the parent QGraphicsItem.
 *
 * Construct a new point on the scene and assign it to the parent graphicCycle.
 */
point::point(struct cycleData data)
{
   fig = data.fig;
   this->x = data.x;
   this->y = data.y;
   this->label = data.label;
   this->scaleFactor = data.relativeScaleFactor;
   this->view = data.view;

   this->setParentItem(data.cycle);

   // create the brush and pen and assign a base colour
   brush = data.brush;
   pen = data.pen;

   setAcceptHoverEvents(true);

}

/*!
 * \brief line::paint Paint the point on the scene.
 * \param p QPainter object.
 *
 * This function paints the point on the scene given various parameters
 * (such as x and y). The point is drawn differently dependent
 * on the drawing metric in use.
 */
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

/*!
 * \brief point::boundingRect Define the bounding rect.
 * \return QRectF
 *
 * Define the box the object is drawn within on the scene.
 */
QRectF point::boundingRect() const
{
    QRectF rect = QRectF(x - POINT_SIZE,
            y - POINT_SIZE,
            20,
            20);

    return rect;
}

///*!
// * \brief point::shape Define the clipping mask of the object
// * \return QPainterPath
// *
// * Defines the area in which hover events take place.
// */
//QPainterPath point::shape() const
//{
//    QPainterPath path;

//    path.addRect(
//        x - POINT_SIZE,
//        y - POINT_SIZE,
//        30,
//        30
//    );



//    return path;
//}

/*!
 * \brief graphicCycle::stableMatrix create new transformation matrix
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

void point::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    emit isHovered();
}

void point::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    emit isUnHovered();
}
