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

    QPointF topLeft = QPointF(-SCENE_SIZE / 2, -SCENE_SIZE / 2);
    QPointF bottomRight = QPointF(SCENE_SIZE / 2, SCENE_SIZE / 2);
    QRectF rect = QRectF(topLeft, bottomRight);

    // set the size of the scene
    this->setSceneRect(rect);
}


/*!
 * \brief graphicsScene::mousePressEvent Mouse pressed on scene
 * \param mouseEvent Provides information about the mouse event such as the position the click occured on the scene.
 *
 * Called when the left mouse button is clicked on the scene in the graphics view.
 */
void graphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF point = mouseEvent->scenePos();

    if (mouseEvent->button() == Qt::LeftButton) {
        // add new point
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
