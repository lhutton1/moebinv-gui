#include <QDebug>
#include "line.h"

line::line(struct cycleData data)
{
   const int SCENE_SIZE = s.value("sceneSize").toInt();

   fig = data.fig;
   this->x = data.x;
   this->y = data.y;
   this->c = data.c;
   this->label = data.label;
   this->relativeScaleFactor = data.relativeScaleFactor;

   this->setParentItem(data.cycle);

   // create the brush and pen and assign a base colour
   brush = data.brush;
   pen = data.pen;

   int sceneSize = SCENE_SIZE;
   if (y == 0) {
       x1 = c / x;

       y2 = -(sceneSize);

       x2 = c / x;

       y1 = sceneSize;
   } else if (x == 0){
       x1 = -(sceneSize);

       y2 = c / y;

       x2 = sceneSize;

       y1 = c / y;
   } else {
       x1 = -(sceneSize);

       y2 = (x * (sceneSize)) + c;

       if (y != 0)
           y2 = y2 / y;

       x2 = sceneSize;

       y1 = (x * -(sceneSize)) + c;

       if (y != 0)
           y1 = y1 / y;
   }

   setPos(x1, y2);
}



void line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // assign brush and pen
        //painter->setBrush(*brush);
        painter->setPen(*pen);

        pen->setCosmetic(true);
        pen->setWidth(s.value("lineWidth").toInt());

        // draw shape
        switch (s.value("drawingMetric").toInt()) {
            case drawingMetric::ELLIPTIC: {
                QLineF line;
                //painter->drawRect(this->boundingRect());
                //painter->drawPath(this->shape());
                // draw line
                if (y == 0) {
                    line = QLineF(0, 0, 0, abs(y2-y1));
                } else if (((-x)/y) > 0) {
                    line = QLineF(0, 0, abs(x2-x1), abs(y2-y1));
                } else if (((-x)/y) < 0) {
                    line = QLineF(0, 0, abs(x2-x1), -abs(y2-y1));
                } else {
                    line = QLineF(0, 0, abs(x2-x1), abs(y2-y1));
                }

                painter->drawLine(line);

                QPointF point(x, y);
                painter->setMatrix(stableMatrix(painter->worldMatrix(), point));

                // add label to side
                // calculate midpoint
                if (s.value("showLabels").toBool()) {
                    double mx = abs(x2-x1) / 2;
                    double my = (abs(y2-y1) / 2);

                    if (y == 0) {
                        painter->drawText(0, -my * (*relativeScaleFactor), label);
                    } else if (x == 0) {
                        painter->drawText(mx * (*relativeScaleFactor), my * (*relativeScaleFactor) - 4, label);
                    } else if (((-x)/y) > 0) {
                        painter->drawText(mx * (*relativeScaleFactor), -my * (*relativeScaleFactor) - 12, label);
                    } else if (((-x)/y) < 0) {
                        painter->drawText(mx * (*relativeScaleFactor), my * (*relativeScaleFactor) + 5, label);
                    }
                }

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
    QPointF topLeft;
    QPointF bottomRight;

    // if padding is less than 15 the label won't be visible
    padding = 15;

    if (y == 0) {
        topLeft = QPointF(-padding, 0);
        bottomRight = QPointF(abs(x2-x1) + padding, abs(y2-y1));
    } else if (x == 0) {
        topLeft = QPointF(0, -padding);
        bottomRight = QPointF(abs(x2-x1), abs(y2-y1) + padding);
    } else if (((-x)/y) > 0) {
        topLeft = QPointF(0, 0);
        bottomRight = QPointF(abs(x2-x1), abs(y2-y1));
    } else if (((-x)/y) < 0) {
        topLeft = QPointF(0, -abs(y2-y1));
        bottomRight = QPointF(abs(x2-x1), 0);
    }

    return QRectF(
        topLeft,
        bottomRight
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
    QPolygonF poly = QPolygonF();

    if (y == 0) {
        poly << QPointF(2, 0)
             << QPointF(abs(x2-x1) + 2, abs(y2-y1))
             << QPointF(abs(x2-x1) - 2, abs(y2-y1))
             << QPointF(-2, 0)
             << QPointF(2, 0);
    } else if (x == 0) {
        poly << QPointF(0, -2)
             << QPointF(abs(x2-x1), -2)
             << QPointF(abs(x2-x1), 2)
             << QPointF(0, 2)
             << QPointF(0, -2);
        ;
    } else if (((-x)/y) > 0) {
        poly << QPointF(2, -2)
             << QPointF(abs(x2-x1) + 2, abs(y2-y1) - 2)
             << QPointF(abs(x2-x1) - 2, abs(y2-y1) + 2)
             << QPointF(-2, 2)
             << QPointF(2, -2);
    } else if (((-x)/y) < 0) {
        poly << QPointF(-2, -2)
             << QPointF(abs(x2-x1) - 2, -abs(y2-y1) - 2)
             << QPointF(abs(x2-x1) + 2, -abs(y2-y1) + 2)
             << QPointF(2, 2)
             << QPointF(-2, -2);
    } else {
        poly << QPointF(0, y2 - 2)
             << QPointF(abs(x2-x1), y1 - 2)
             << QPointF(abs(x2-x1), y1 + 2)
             << QPointF(0, y2 + 2)
             << QPointF(0, y2 - 2);
    }

    path.addPolygon(poly);

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

