#include <QDebug>
#include "scene.h"

/*!
 * \brief Scene Constructor.
 * \param parent The parent widget to the current widget.
 *
 * continued description....
 */
graphicsScene::graphicsScene(QObject *parent)
    : QGraphicsScene(parent)
{

}

/*!
 * \brief graphicsScene::mousePressEvent Mouse pressed on scene
 * \param mouseEvent Provides information about the mouse event such as the position the click occured on the scene.
 *
 * Called when the mouse is clicked on the scene in the graphics view.
 */
void graphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton) {
        QPointF point = mouseEvent->scenePos();
        emit newMousePress(point);
    }
}

