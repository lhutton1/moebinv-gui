#include <QDebug>
#include "view.h"

/*!
 * \brief view::view Construct a new view.
 * \param parent parent object to the view.
 *
 * Construct a new view applying any settings.
 */
view::view(QObject *parent)
{
    const int initialZoomFactor = s.value("initialZoomFactor").toInt();

    // reflect the y-axis so coordinate system matches a standard graph
    this->scale(initialZoomFactor, -initialZoomFactor);
    this->setRenderHint(QPainter::Antialiasing);
    this->relativeScaleFactor = 1;

    // set timer to detect when mouse stops
    this->mouseTimeOut = new QTimer(this);
    connect(mouseTimeOut, &QTimer::timeout, this, &view::mouseStopped);
    this->mouseTimeOut->start(s.value("mouseStopWait").toInt());
}


/*!
 * \brief view::wheelEvent Implements zooming on scroll wheel.
 * \param event Mouse wheel event.
 *
 * When the scroll wheel is used the view will either zoom in or out depending on the scroll wheel direction.
 */
void view::wheelEvent(QWheelEvent * event)
{
    const ViewportAnchor anchor = transformationAnchor();
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    int angle = event->angleDelta().y();
    qreal factor;

    if (angle > 0) {
        factor = 1.1;
        relativeScaleFactor *= 1.1;
    } else {
        factor = 0.9;
        relativeScaleFactor *= 0.9;
    }

    scale(factor, factor);
    setTransformationAnchor(anchor);
    setViewportUpdateMode(FullViewportUpdate);
}


/*!
 * \brief view::recenterView Recenter the view
 *
 * Recenter the view to the default point (0, 0).
 */
void view::recenterView()
{
    this->centerOn(QPointF(0, 0));
}


/*!
 * \brief view::mouseMoveEvent
 * \param event
 *
 * Reimplemented event that is triggered when the mouse moves on the view.
 */
void view::mouseMoveEvent(QMouseEvent *event)
{
    // Implement old mouse move event and then add to it
    QGraphicsView::mouseMoveEvent(event);

    // Start a timer to be used to detect when the mouse has stopped moving
    if (!mouseTimeOut->isActive())
        mouseTimeOut->start();

    mouseTimeOut->setInterval(s.value("mouseStopWait").toInt());
}


/*!
 * \brief view::mouseStopped
 *
 * Slot that is triggered when the mouse has stopped moving.
 * This slot then emits a signal to find the closest cycle to
 * the current mouse position.
 */
void view::mouseStopped()
{
    mouseTimeOut->stop();

    QPoint point = this->mapFromGlobal(QCursor::pos());
    QPointF relPoint = this->mapToScene(point);

    emit highlightClosestCycle(relPoint);
}


/*!
 * \brief view::zoomIn
 *
 * Zoom in by a constant factor.
 */
void view::zoomIn()
{
    qreal factor = 1 + s.value("zoomFactorAmount").toDouble();

    relativeScaleFactor *= factor;
    scale(factor, factor);
}


/*!
 * \brief view::zoomOut
 *
 * Zoom out by a constant factor.
 */
void view::zoomOut()
{
    qreal factor = 1 - s.value("zoomFactorAmount").toDouble();

    relativeScaleFactor *= factor;
    scale(factor, factor);
}
