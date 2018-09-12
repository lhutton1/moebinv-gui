#include <QDebug>
#include "line.h"


/*!
 * \brief line::line Create a new line.
 * \param struct cycleData data Contains the data needed to draw the line.
 *
 * Construct a new line on the scene and assign it to the parent graphicCycle.
 */
line::line(graphicCycle *parent, struct cycleData data)
{
    this->parent = parent;
    this->scaleFactor = parent->getRelativeScaleFactor();
    this->label = parent->getCycleLabel();

    this->x = data.x;
    this->y = data.y;
    this->c = data.c;
    this->brush = data.brush;
    this->pen = data.pen;

    this->findLinePoints();

    this->setParentItem(parent);
    this->setPos(x1, y1);
}


/*!
 * \brief line::paint Paint the point on the scene.
 * \param p QPainter object.
 * \param option
 * \param widget
 *
 * This function paints the line on the scene given various parameters
 * (such as x and y). The line is drawn differently dependent
 * on the drawing metric in use.
 */
void line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QLineF line;
    QPointF point(0, 0);
    const double sf = s.value("initialZoomFactor").toInt() * (*scaleFactor);

    // assign brush and pen to the painter.
    //painter->setBrush(*brush);
    painter->setPen(*pen);

    // draw shape
    switch (s.value("drawingMetric").toInt()) {
        case drawingMetric::ELLIPTIC: {
            // draw line
            if (y == 0) // vertical line
                line = QLineF(0, 0, 0, abs(y2-y1));
            else if (((-x)/y) > 0) // line with positive gradient
                line = QLineF(0, 0, abs(x2-x1), abs(y2-y1));
            else if (((-x)/y) < 0) // line with negative gradient
                line = QLineF(0, 0, abs(x2-x1), -abs(y2-y1));
            else if (x == 0) // horizontal line
                line = QLineF(0, 0, abs(x2-x1), abs(y2-y1));

            painter->drawLine(line);

            // set the painter matrix to correct size for zoom
            painter->setMatrix(parent->stableMatrix(painter->worldMatrix(), point));

            // add label to side
            if (s.value("showLabels").toBool()) {
                double mx = abs(x2-x1) / 2;
                double my = abs(y2-y1) / 2;

                if (y == 0) // vertical line
                    painter->drawText(3, -(my * sf), label);
                else if (((-x)/y) > 0) // line with positive gradient
                    painter->drawText(mx * sf, -(my * sf) - 7, label);
                else if (((-x)/y) < 0) // line with negative gradient
                    painter->drawText(mx * sf, (my * sf), label);
                else if (x == 0) // horizontal line
                    painter->drawText(mx * sf, -3, label);
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


/*!
 * \brief line::boundingRect Define the bounding rect.
 * \return QRectF
 *
 * Define the box the object is drawn within on the scene.
 */
QRectF line::boundingRect() const
{
    double padding;
    QPointF topLeft;
    QPointF bottomRight;

    // if padding is less than 15 the label won't be visible
    padding = (15 / s.value("initialZoomFactor").toDouble()) / (*scaleFactor);

    if (y == 0) { // vertical line
        topLeft = QPointF(-padding, 0);
        bottomRight = QPointF(abs(x2-x1) + padding, abs(y2-y1));
    } else if (x == 0) { // horizontal line
        topLeft = QPointF(0, -padding);
        bottomRight = QPointF(abs(x2-x1), abs(y2-y1) + padding);
    } else if (((-x)/y) > 0) { // line with positive gradient
        topLeft = QPointF(0, 0);
        bottomRight = QPointF(abs(x2-x1), abs(y2-y1));
    } else if (((-x)/y) < 0) { // line with negative gradient
        topLeft = QPointF(0, -abs(y2-y1));
        bottomRight = QPointF(abs(x2-x1), 0);
    }

    return QRectF(
        topLeft,
        bottomRight
    );
}


/*!
 * \brief line::shape Define the clipping mask of the object
 * \return QPainterPath
 *
 * Defines the area in which the shape actually exists.
 */
//QPainterPath line::shape() const {
//    QPainterPath path;
//    QPolygonF poly = QPolygonF();
//    const double sf = s.value("initialZoomFactor").toInt() * (*scaleFactor);

//    if (y == 0) { // vertical line
//        poly << QPointF(2 * sf, 0)
//             << QPointF(abs(x2-x1) + 2 * sf, abs(y2-y1))
//             << QPointF(abs(x2-x1) - 2 * sf, abs(y2-y1))
//             << QPointF(-2 * sf, 0)
//             << QPointF(2 * sf, 0);
//    } else if (x == 0) { // horizontal line
//        poly << QPointF(0, (-2 / sf))
//             << QPointF(abs(x2-x1), (-2 / sf))
//             << QPointF(abs(x2-x1), (2 / sf))
//             << QPointF(0, (2 / sf))
//             << QPointF(0, -2 / sf);
//    } else if (((-x)/y) > 0) { // line with positive gradient
//        poly << QPointF(2, -2)
//             << QPointF(abs(x2-x1) + 2, abs(y2-y1) - 2)
//             << QPointF(abs(x2-x1) - 2, abs(y2-y1) + 2)
//             << QPointF(-2, 2)
//             << QPointF(2, -2);
//    } else if (((-x)/y) < 0) { // line with negative gradient
//        poly << QPointF(-2, -2)
//             << QPointF(abs(x2-x1) - 2, -abs(y2-y1) - 2)
//             << QPointF(abs(x2-x1) + 2, -abs(y2-y1) + 2)
//             << QPointF(2, 2)
//             << QPointF(-2, -2);
//    }

//    path.addPolygon(poly);

//    return path;
//}


/*!
 * \brief line::findLinePoints Find the points: (x1, y1), (x2, y2).
 *
 * This function finds the two points in which the line will be drawn between.
 * Hence since we need to draw a line accross the whole of the scene, we find two
 * points which are beyond the scene and draw the line between those.
 */
void line::findLinePoints()
{
    const int SCENE_SIZE = s.value("sceneSize").toInt();

    if (y == 0) { // vertical line
        x1 = c / x;
        y1 = -(SCENE_SIZE);
        x2 = c / x;
        y2 = SCENE_SIZE;

    } else if (x == 0){ // horizontal line
        x1 = -(SCENE_SIZE);
        y1 = c / y;
        x2 = SCENE_SIZE;
        y2 = c / y;

    } else { // diagonal line
        x1 = -(SCENE_SIZE);
        y1 = (x * (SCENE_SIZE)) + c;

        x2 = SCENE_SIZE;
        y2 = (x * -(SCENE_SIZE)) + c;

        if (y != 0) {
            y1 = y1 / y;
            y2 = y2 / y;
        }
    }
}

