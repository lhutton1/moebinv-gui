#include <QDebug>
#include "graphiccycle.h"

using namespace GiNaC;
using namespace MoebInv;

/*!
 * \brief graphicCycle::graphicCycle graphicd cycle constructor.
 * \param f MoebInv::figure
 * \param c GiNaC::ex the cycle that the graphicCycle represents.
 * \param relativeScaleFactor the scale factor of the scene.
 * \param menu the menu that the graphic cycle is linked to.
 * \param styleData the data to style the graphic cycle such as colour.
 */
graphicCycle::graphicCycle(figure *f, ex c, double *relativeScaleFactor, cycleContextMenu *menu, struct cycleStyleData styleData)
{
    this->f = f;
    this->cycle = c;
    this->menu = menu;
    this->relativeScaleFactor = relativeScaleFactor;
    this->styleData = styleData;
    this->msgBox = new QMessageBox();
    this->itemIsHighlighted = false;
    this->itemIsGrabbed = false;
    this->itemIsAbleToMove = false;
    this->itemIsPoint = false;

    // create the brush and pen and assign settings
    brush = new QBrush(styleData.colour);
    pen = new QPen(styleData.colour);
    pen->setCosmetic(true);
    pen->setWidth(styleData.lineWidth);

    if (styleData.lineStyle == SOLID)
        pen->setStyle(Qt::SolidLine);
    else if (styleData.lineStyle == DOTTED)
        pen->setStyle(Qt::DotLine);
    else if (styleData.lineStyle == DASHED)
        pen->setStyle(Qt::DashLine);

    connect(menu, &cycleContextMenu::cycleStyleChanged, this, &graphicCycle::setCycleStyle);

    // create the shape and add the necessary child graphicsItems.
    buildShape();

    // set timer to detect when mouse stops
    this->mouseTimeOut = new QTimer(this);
    connect(mouseTimeOut, &QTimer::timeout, this, &graphicCycle::mouseStopped);
    this->mouseTimeOut->start(s.value("mouseStopWait").toInt());
}


/*!
 * \brief graphicCycle::getCycleLabel get the cycle label.
 * \return  QString
 */
QString graphicCycle::getCycleLabel()
{
    return node_label(this->cycle);
}



/*!
 * \brief graphicCycle::getRelativeScaleFactor get the scale factor of the scene.
 * \return double*
 */
double* graphicCycle::getRelativeScaleFactor()
{
    return this->relativeScaleFactor;
}


/*!
 * \brief graphicCycle::getContextMenu get the context menu linked to the scene.
 * \return cycleContextMenu*
 */
cycleContextMenu* graphicCycle::getContextMenu()
{
    cycleContextMenu* menuP = QPointer<cycleContextMenu>(menu);

    if (menuP)
        return menuP;
}


/*!
 * \brief graphicCycle::getItemIsGrabbed get whether the item is being moved.
 */
bool graphicCycle::getItemIsGrabbed()
{
    return itemIsGrabbed;
}


/*!
 * \brief graphicCycle::setColour set the colour of the graphic cycle.
 * \param colour
 *
 * Set the colour of the graphic cycle, by building the relevent styleData.
 */
void graphicCycle::setColour(QColor colour)
{
    this->styleData.colour = colour;
    this->styleData.isDefault = false;
    setCycleAsy(this->cycle, this->styleData);
    emit sceneInvalid();
}


/*!
 * \brief graphicCycle::setLineWidth set the weight of the graphic cycle.
 * \param weight
 *
 * Set the weight of the graphic cycle, by building the relevent styleData.
 */
void graphicCycle::setLineWidth(double weight)
{
    this->styleData.lineWidth = weight;
    this->styleData.isDefault = false;
    setCycleAsy(this->cycle, this->styleData);
    emit sceneInvalid();
}


/*!
 * \brief graphicCycle::setLineStyle set the style of the graphic cycle.
 * \param style
 *
 * Set the style of the graphic cycle, by building the relevent styleData.
 */
void graphicCycle::setLineStyle(int style)
{
    this->styleData.lineStyle = style;
    this->styleData.isDefault = false;
    setCycleAsy(this->cycle, this->styleData);
    emit sceneInvalid();
}

void graphicCycle::setCycleStyle(const struct cycleStyleData &data)
{
    setCycleAsy(this->cycle, data);
    emit sceneInvalid();
}


/*!
 * \brief graphicCycle::stableMatrix create new transformation matrix
 * \param matrix the current transformation matrix
 * \param p point at which the transformation is centered
 * \return QMatrix - the new transformation matrix
 *
 * Create a new matrix which will keep items the same size when the zoom transformation is applied to it.
 */
QMatrix graphicCycle::stableMatrix(const QMatrix &matrix, const QPointF &p)
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


/*!
 * \brief graphicCycle::boundingRect Define the bounding rect.
 * \return QRectF
 *
 * Define the box the object is drawn within on the scene. This is done by getting all of the
 * children bounding rectangles and combining them.
 */
QRectF graphicCycle::boundingRect() const
{
    return this->childrenBoundingRect();
}


/*!
 * \brief graphicCycle::paint Paint the object to the scene.
 * \param painter
 * \param option
 * \param widget
 *
 * Painting of individual objects is done by each of the children.
 * However, the pen and brush still need to be set.
 */
void graphicCycle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(*this->pen);

    if (s.value("debugBoundingRect").toBool())
        painter->drawRect(this->boundingRect());
    else
        painter->setBrush(*this->brush);

}


/*!
 * \brief graphicCycle::addChild Add a new child to graphic cycle.
 * \param childType the type of child object to be drawn e.g. point, circle, line.
 * \param x the x value the object will be drawn at.
 * \param y the y value the object will be drawn at.
 * \param c the value of c (for lines).
 * \param radius the radius of the object (for circles).
 *
 * Add a new child to this graphic cycle. This could consist of any type in the enum 'childType'.
 */
void graphicCycle::addChild(int childType, const double &x, const double &y, const double &c, const double &radius)
{
    struct cycleData data;
    data.x = x;
    data.y = y;
    data.c = c;
    data.radius = radius;
    data.brush = this->brush;
    data.pen = this->pen;

    switch (childType) {
        case POINT:
            new class point(this, data);
            break;
        case CIRCLE:
            new class circle(this, data);
            break;
        case LINE:
            new class line(this, data);
            break;
    }
}


/*!
 * \brief graphicCycle::buildShape build the shape.
 *
 * Build the shape by adding the necessary children to the graphic cycle.
 * If any child cannot be drawn graphically then MoebInv will thow an exception,
 * this is caught and a message is shown in the debugger.
 */
void graphicCycle::buildShape()
{
    ex cycle = f->get_cycles(this->cycle);

    // try to draw new cycle, if not display an error message
    try {
        // interate through cycle components
        for (auto cycleItems : cycle) {
            cycle2D C = ex_to<cycle2D>(cycleItems);

            if (ex_to<numeric>(abs(C.radius_sq()).evalf()).to_double() < EPSILON) {
                double x = ex_to<numeric>(C.center().op(0).evalf()).to_double();
                double y = ex_to<numeric>(C.center().op(1).evalf()).to_double();
                addChild(POINT, x, y);

                this->setZValue(200);
                this->itemIsPoint = true;

                if (f->get_generation(this->cycle) == 0) {
                    this->itemIsAbleToMove = true;
                    this->setFlag(ItemIsMovable);
                }

            } else if (ex_to<numeric>(abs(C.get_k()).evalf()).to_double() < EPSILON) {
                double x = ex_to<numeric>(C.get_l(0).evalf()).to_double();
                double y = ex_to<numeric>(C.get_l(1).evalf()).to_double();
                double c = ex_to<numeric>((C.get_m()/2).evalf()).to_double();
                addChild(LINE, x, y, c);

            } else {
                double x = ex_to<numeric>(C.center().op(0).evalf()).to_double();
                double y = ex_to<numeric>(C.center().op(1).evalf()).to_double();
                double radius_sq = ex_to<numeric>(C.radius_sq().evalf()).to_double();

                if (radius_sq >= 0) {
                    double radius = sqrt(radius_sq);
                    addChild(CIRCLE, x, y, 0, radius);
                }
            }
        }
    } catch(...) {
        qDebug() << "Too many or too little conditions are specified";
    }
}


/*!
 * \brief graphicCycle::setHover set the hover style of the object.
 *
 * Set the hover style of the object by retreiving the relevent global settings
 * and setting the pen and brush accordingly.
 */
void graphicCycle::setHover()
{
    // set the colour of both the pen and brush, then update the item.
    brush->setColor(s.value("session/graphicsHoverColour").value<QColor>());
    pen->setColor(s.value("session/graphicsHoverColour").value<QColor>());
    this->itemIsHighlighted = true;
    this->update();

    // now emit signal to find in tree
    emit findCycleInTree(this->cycle);
}


/*!
 * \brief graphicCycle::unsetHover unset the object hover
 *
 * Reset the object to its original style.
 */
void graphicCycle::unsetHover()
{
    // set the colour of both the pen and brush, then update the item.
    brush->setColor(this->styleData.colour);
    pen->setColor(this->styleData.colour);
    this->itemIsHighlighted = false;
    this->update();
}


/*!
 * \brief graphicCycle::mousePressEvent reimplements mouse press event.
 * \param event mouse event.
 *
 * Reimplements mouse press event to allow movement of a point when it is highlighted.
 */
void graphicCycle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);

    if (event->button() == Qt::LeftButton && this->itemIsHighlighted && this->itemIsPoint && !this->itemIsAbleToMove) {
        msgBox->warning(0, "Point cannot be moved", "This cycle is not of generation 0 so cannot be moved");
        return;
    }

    if (event->button() == Qt::LeftButton && this->itemIsHighlighted && this->itemIsAbleToMove) {
        this->sceneX = event->scenePos().x();
        this->sceneY = event->scenePos().y();
        this->itemIsGrabbed = true;
    }
}


/*!
 * \brief graphicCycle::mouseMoveEvent
 * \param event
 *
 * Detect whether the mouse has been moved.
 */
void graphicCycle::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (!this->itemIsGrabbed)
        return;

    QGraphicsItem::mouseMoveEvent(event);
}

/*!
 * \brief graphicCycle::mouseReleaseEvent reimplements the mouse release event.
 * \param event mouse event.
 *
 * Reimplements the mouse release event to allow movement of a point when it is highlighted.
 */
void graphicCycle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);

    if (event->button() == Qt::LeftButton && this->itemIsHighlighted) {
        if (sceneX != event->scenePos().x() || sceneY != event->scenePos().y()) {
            // move the point in the figure.
            MoebInv::figure originalFigure = *this->f;
            this->f->move_point(cycle, lst(event->scenePos().x(), event->scenePos().y()));
            MoebInv::figure changedFigure = *this->f;
            emit changesMadeToFigure(originalFigure, changedFigure);
        }
        this->itemIsGrabbed = false;
        emit sceneInvalid();
    }
}


/*!
 * \brief graphicCycle::mouseStopped
 *
 * Timer slot triggered when the mouse has timed out. This is used to
 * detect when the mouse has stopped moving on the scene.
 */
void graphicCycle::mouseStopped()
{
    mouseTimeOut->stop();

    if (this->itemIsGrabbed) {
        QPointF relPoint = this->mapToScene(this->scenePos());
        this->f->move_point(cycle, lst(relPoint.x(), relPoint.y()));
        emit sceneInvalid();
    }
}


/*!
 * \brief graphicCycle::cancelMovement
 *
 * Cancels a movement when a generation 0 has been grabbed
 * and is currently being moved.
 */
void graphicCycle::cancelMovement()
{
    if (this->itemIsGrabbed) {
        emit sceneInvalid();
    }
}

// REMOVE....
QString graphicCycle::node_label(GiNaC::ex name)
{
    std::ostringstream drawing;
    drawing << name;
    string dr = drawing.str().c_str();

    return QString::fromStdString(dr);
}

bool graphicCycle::setCycleAsy(const ex &new_cycle, const struct cycleStyleData &data)
{
    QString asyString;
    QString red, green, blue;
    QString lineWidth;
    QString lineStyle;

    red = QString::number(data.colour.red() / 255.0);
    green = QString::number(data.colour.green() / 255.0);
    blue = QString::number(data.colour.blue() / 255.0);
    lineWidth = QString::number(data.lineWidth) + "pt";

    switch (data.lineStyle) {
        case SOLID:
            lineStyle = "solid";
            break;
        case DOTTED:
            lineStyle = "dotted";
            break;
        case DASHED:
            lineStyle = "dashed";
            break;
    }

    asyString = "rgb(" + red + "," + green + "," + blue + ")" + "+" +
                lineStyle + "+" +
                lineWidth;

    MoebInv::figure originalFigure = *this->f;

    try {
        f->set_asy_style(new_cycle, qPrintable(asyString));
    } catch (...) {
        return false;
    }

    MoebInv::figure changedFigure = *this->f;
    changesMadeToFigure(originalFigure, changedFigure);

    return true;
}

