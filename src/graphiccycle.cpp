#include <QDebug>
#include "graphiccycle.h"

using namespace GiNaC;
using namespace MoebInv;

/*!
 * \brief graphicCycle::graphicCycle
 * \param f Moebinv figure provides access to the cycle data stored in the library.
 * \param c The cycle that has just been created and added to the figure.
 * \param l The label used by the cycle as a unique identifier.
 */

graphicCycle::graphicCycle(figure *f, ex c, class view *v, double *relativeScaleFactor, cycleContextMenu *menu, QColor colour)
{
    // assign parameters
    this->fig = f;
    this->cycle = c;
    this->label = node_label(c);
    this->relativeScaleFactor = relativeScaleFactor;
    this->view = v;
    this->colour = colour;
    this->lineStyle = 0;
    this->lineWidth = 1;

//    if (fig->get_asy_style(cycle).length() != 0) {
//        QString s = QString::fromStdString(fig->get_asy_style(cycle));
//        QColor c = s;
//        this->defaultColour = c;
//    } else {
//        this->defaultColour = s.value("defaultGraphicsColour").value<QColor>();
//    }

    // create the brush and pen and assign a base colour
    brush = new QBrush(colour);
    pen = new QPen(colour);
    pen->setCosmetic(true);

    // create a new menu to be used when the user right clicks on the object
    this->menu = menu;
    connect(menu, &cycleContextMenu::colourSelected, this, &graphicCycle::setStyle);

    // connect signals
    //connect(menu->deletePoint, &QAction::triggered, this, &graphicCycle::removeCycle);
    //connect(menu->changeColour, &QAction::triggered, this, &graphicCycle::showColourDialog);
    //connect(colourDialog, &QColorDialog::colorSelected, this, &graphicCycle::setColour);

    // allow hover events to take place, used to highlight
    // currently hovered object on the scene
    setAcceptHoverEvents(true);

    buildShape();
}

/*!
 * \brief graphicCycle::contextMenuEvent Menu popup for cycle.
 * \param event new mouse event.
 *
 * Detects when a menu is being requested (i.e. right click) on a cycle.
 * This gives the user the option to delete the point and set relevent relations.
 */
//void graphicCycle::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
//{
//    menu->popup(event->screenPos());
//}

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

void graphicCycle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // set pen
    painter->setBrush(*brush);
    painter->setPen(*pen);
}

void graphicCycle::addPoint(double x, double y, double *relativeScaleFactor)
{
    struct cycleData data;
    data.x = x;
    data.y = y;
    data.radius = 0;
    data.c = 0;
    data.label = label;
    data.cycle = this;
    data.fig = fig;
    data.relativeScaleFactor = relativeScaleFactor;
    data.brush = brush;
    data.pen = pen;
    data.view = view;

    class point *p = new class point(relativeScaleFactor, data);
}

void graphicCycle::addCircle(double x, double y, double radius, double *relativeScaleFactor)
{
    struct cycleData data;
    data.x = x;
    data.y = y;
    data.radius = radius;
    data.c = 0;
    data.label = label;
    data.cycle = this;
    data.fig = fig;
    data.relativeScaleFactor = relativeScaleFactor;
    data.brush = brush;
    data.pen = pen;
    data.view = view;

    class circle *c = new class circle(data);
}

void graphicCycle::addLine(double x, double y, double c, double *relativeScaleFactor)
{
    struct cycleData data;
    data.x = x;
    data.y = y;
    data.radius = 0;
    data.c = c;
    data.label = label;
    data.cycle = this;
    data.fig = fig;
    data.relativeScaleFactor = relativeScaleFactor;
    data.brush = brush;
    data.pen = pen;
    data.view = view;

    class line *l = new class line(relativeScaleFactor, data);
}

QRectF graphicCycle::boundingRect() const
{
    return this->childrenBoundingRect();
}

void graphicCycle::buildShape()
{
    ex L = fig->get_cycle(cycle);
    bool isOntop = false;

    // try to draw new cycle, if not emit a signal to display error message.
    try {
        // interate through cycle components
        for (lst::const_iterator it =ex_to<lst>(L).begin(); it != ex_to<lst>(L).end(); ++it) {
            cycle2D C = ex_to<cycle2D>(*it);

            if (ex_to<numeric>(abs(C.radius_sq()).evalf()).to_double() < EPSILON) {
                //point
                double x = ex_to<numeric>(C.center().op(0).evalf()).to_double();
                double y = ex_to<numeric>(C.center().op(1).evalf()).to_double();

                addPoint(x, y, relativeScaleFactor);
                isOntop = true;

            } else if (ex_to<numeric>(abs(C.get_k()).evalf()).to_double() < EPSILON) {
                //line
                double x = ex_to<numeric>(C.get_l(0).evalf()).to_double();
                double y = ex_to<numeric>(C.get_l(1).evalf()).to_double();
                double c = ex_to<numeric>((C.get_m()/2).evalf()).to_double();

                addLine(x, y, c, relativeScaleFactor);
            } else {
                //circle
                double x = ex_to<numeric>(C.center().op(0).evalf()).to_double();
                double y = ex_to<numeric>(C.center().op(1).evalf()).to_double();
                double radius = qSqrt(ex_to<numeric>(C.radius_sq().evalf()).to_double());
                addCircle(x, y, radius, relativeScaleFactor);
            }
        }
    } catch(...) {
        qDebug() << "Too many or too little conditions are specified";
    }

    if (isOntop)
        this->setZValue(1);
    else
        this->setZValue(-1);
}

QString graphicCycle::node_label(GiNaC::ex name)
{
    std::ostringstream drawing;
    drawing << name;
    string dr = drawing.str().c_str();

    return QString::fromStdString(dr);
}

void graphicCycle::setHover()
{
    brush->setColor(s.value("graphicsHoverColour").value<QColor>());
    pen->setColor(s.value("graphicsHoverColour").value<QColor>());
    this->update();

    // now emit signal to find in tree
    emit findCycleInTree(cycle);
}

void graphicCycle::unsetHover()
{
    brush->setColor(this->colour);
    pen->setColor(this->colour);
    this->update();
}

void graphicCycle::setStyle(QColor colour)
{
    this->colour = colour;

    struct cycleStyleData data;
    data.colour = colour;
    data.lineStyle = this->lineStyle;
    data.lineWidth = this->lineWidth;
    setCycleAsy(this->cycle, data);
    emit sceneInvalid();
}

QPointer<cycleContextMenu> graphicCycle::getContextMenu()
{
    QPointer<cycleContextMenu> menuP = QPointer<cycleContextMenu>(menu);

    if (!menuP.isNull())
        return menuP;
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

    try {
        fig->set_asy_style(new_cycle, qPrintable(asyString));
    } catch (...) {
        return false;
    }

    return true;
}

