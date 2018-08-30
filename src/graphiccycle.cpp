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

graphicCycle::graphicCycle(figure *f, ex c, class view *v, double *relativeScaleFactor, cycleContextMenu *menu)
{
    // assign parameters
    this->fig = f;
    this->cycle = c;
    this->label = node_label(c);
    this->relativeScaleFactor = relativeScaleFactor;
    this->view = v;

    if (fig->get_asy_style(cycle).length() != 0) {
        QString s = QString::fromStdString(fig->get_asy_style(cycle));
        QColor c = s;
        this->defaultColour = c;
    } else {
        this->defaultColour = s.value("defaultGraphicsColour").value<QColor>();
    }


    colourDialog = new QColorDialog();

    // create the brush and pen and assign a base colour
    brush = new QBrush(Qt::black);
    pen = new QPen(Qt::black);

    // create a new menu to be used when the user right clicks on the object
    this->menu = menu;

    // connect signals
    connect(menu, &cycleContextMenu::addRelationToList, this, &graphicCycle::addToList);
    connect(menu, &cycleContextMenu::removeRelationFromList, this, &graphicCycle::removeFromList);
    connect(menu->deletePoint, &QAction::triggered, this, &graphicCycle::removeCycle);
    connect(menu->changeColour, &QAction::triggered, this, &graphicCycle::showColourDialog);
    connect(colourDialog, &QColorDialog::colorSelected, this, &graphicCycle::setColour);

    // allow hover events to take place, used to highlight
    // currently hovered object on the scene
    setAcceptHoverEvents(true);

    msgBox = new QMessageBox();

    buildShape();
}

/*!
 * \brief graphicCycle::contextMenuEvent Menu popup for cycle.
 * \param event new mouse event.
 *
 * Detects when a menu is being requested (i.e. right click) on a cycle.
 * This gives the user the option to delete the point and set relevent relations.
 */
void graphicCycle::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    menu->popup(event->screenPos());
}

/*!
 * \brief graphicCycle::resetRelationalList Uncheck all relations from menu.
 */
void graphicCycle::resetRelationalList()
{
    menu->isOrthogonal->setChecked(false);
    menu->isfOrthogonal->setChecked(false);
    menu->isTangent->setChecked(false);
    menu->isDifferent->setChecked(false);
}

/*!
 * \brief graphicCycle::addToList
 * \param relType
 *
 * Slot to add a certain cycle to the list. Emmits a signal to call slot
 * in MainWindow to add the cycle to the list.
 */
void graphicCycle::addToList(int relType)
{
    emit addRelationToList(relType, cycle);
}

/*!
 * \brief graphicCycle::removeFromList
 *
 * Slot to remove cycle from list. Emmits a signal to call slot in
 * MainWindow to remove the cycle from the list.
 */
void graphicCycle::removeFromList(int relType)
{
    emit removeRelationFromList(relType, cycle);
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

    class point *p = new class point(data);
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

    class line *l = new class line(data);
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
                double x = ex_to<numeric>(C.center().op(0)).to_double();
                double y = ex_to<numeric>(C.center().op(1)).to_double();
                double radius = qSqrt(ex_to<numeric>(C.radius_sq()).to_double());
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

void graphicCycle::removeCycle()
{
    fig->remove_cycle_node(cycle);
    emit sceneInvalid();
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
    update();

    // now emit signal to find in tree
    emit findCycleInTree(cycle);
}

void graphicCycle::setColour(QColor color)
{
    QString asyStyle = "rgb(" + QString::number(color.redF())
            + "," + QString::number(color.greenF())
            + "," + QString::number(color.blueF());

    fig->set_asy_style(cycle, qPrintable(asyStyle));
    defaultColour = color;
    brush->setColor(color);
    pen->setColor(color);
    update();
}

void graphicCycle::unsetHover()
{
    brush->setColor(Qt::black);
    pen->setColor(Qt::black);
    update();
}

QPointer<cycleContextMenu> graphicCycle::getContextMenu()
{
    QPointer<cycleContextMenu> menuP = QPointer<cycleContextMenu>(menu);

    if (!menuP.isNull())
        return menuP;
}

void graphicCycle::showColourDialog()
{
    colourDialog->open();

}

