#include <QDebug>
#include "scene.h"

using namespace GiNaC;
using namespace MoebInv;

/*!
 * \brief Scene Constructor.
 * \param parent The parent widget to the current widget.
 *
 * Create a new scene setting the scene size to the predetermined size.
 */
graphicsScene::graphicsScene(QObject *parent)
    : QGraphicsScene(parent)
{
    const int SCENE_SIZE = s.value("sceneSize").toInt();

    this->pointIsHighlighted = false;

    // set the size of the scene
    QPointF topLeft = QPointF(-SCENE_SIZE / 2, -SCENE_SIZE / 2);
    QPointF bottomRight = QPointF(SCENE_SIZE / 2, SCENE_SIZE / 2);
    QRectF rect = QRectF(topLeft, bottomRight);
    this->setSceneRect(rect);
}


/*!
 * \brief graphicsScene::getPointIsHighlighted getter for pointIsHighlighted.
 * \return bool
 *
 * PointIsHighlighted represents a boolean value that determines if a point is being hovered or not.
 */
bool graphicsScene::getPointIsHighlighted()
{
    return this->pointIsHighlighted;
}


/*!
 * \brief graphicsScene::setPointIsHighlighted setter for pointIsHighlighted.
 * \param value
 *
 * PointIsHighlighted represents a boolean value that determines if a point is being hovered or not.
 */
void graphicsScene::setPointIsHighlighted(const bool &value)
{
    this->pointIsHighlighted = value;
}



/*!
 * \brief graphicsScene::mousePressEvent Mouse pressed on scene
 * \param mouseEvent Provides information about the mouse event such as the position the click occured on the scene.
 *
 * Called when the mouse button is clicked on the scene in the graphics view. A left mouse click will mean a new point
 * is created or the highlighted point is moved. A right mouse click will display the context menu.
 */
void graphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF point = mouseEvent->scenePos();
    QGraphicsScene::mousePressEvent(mouseEvent);

    if (mouseEvent->button() == Qt::LeftButton && !this->pointIsHighlighted) {
        // if a point is highlighted, get ready to move. Else add new point.
        emit newMouseLeftPress(point);
    } else if (mouseEvent->button() == Qt::RightButton) {
        // display highlighted cycles context menu
        emit newMouseRightPress(point);
    }
}


/*!
 * \brief graphicsScene::mouseMoveEvent Mouse moved on scene.
 * \param mouseEvent Provides information about the mouse event such as the position the click occured on the scene.
 *
 * Called when the mouse moves over the scene. Signal is emitted to update coordinates on the status bar.
 */
void graphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    // Whilst we need to reimplement the mouse move event,
    // we still need everything that the base function does
    QGraphicsScene::mouseMoveEvent(mouseEvent);

    // Now send signal to update status bar
    QPointF point = mouseEvent->scenePos();

    emit newMouseHover(point);
}
