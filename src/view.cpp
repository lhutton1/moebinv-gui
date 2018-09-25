#include <QDebug>
#include "view.h"

/*!
 * \brief view::view Construct a new view.
 * \param parent parent object to the view.
 *
 * Construct a new view applying any settings.
 */
view::view(QWidget *parent)
{
    const int initialZoomFactor = s.value("initialZoomFactor").toInt();

    this->scale(initialZoomFactor, -initialZoomFactor); // reflect the y-axis so coordinate system matches a standard graph
    this->setRenderHint(QPainter::Antialiasing);
    this->setParent(parent);
    this->setViewportUpdateMode(FullViewportUpdate);

    this->relativeScaleFactor = 1;
    this->panningActive = false;
    this->panningEnabled = false;
    this->contextMenu = nullptr;
    this->currentHighlightedCycle = nullptr;

    // set timer to detect when mouse stops
    this->mouseTimeOut = new QTimer(this);
    connect(mouseTimeOut, &QTimer::timeout, this, &view::mouseStopped);
    this->mouseTimeOut->start(s.value("mouseStopWait").toInt());
}


/*!
 * \brief view::getPanningEnabled getter for panning enabled.
 * \return bool
 */
bool view::getPanningEnabled()
{
    return this->panningEnabled;
}


/*!
 * \brief view::getCurrentHighlightedCycle getter for currentHighlightedCycle.
 * \return graphicCycle
 */
QPointer<graphicCycle> view::getCurrentHighlightedCycle()
{
    return this->currentHighlightedCycle;
}


/*!
 * \brief view::setPanningEnabled setter for panning enabled.
 * \param value
 */
void view::setPanningEnabled(const bool &value)
{
    this->panningEnabled = value;
}


/*!
 * \brief view::setCurrentHighlightedCycle setter for currently highlighted cycle.
 * \param cycle
 */
void view::setCurrentHighlightedCycle(const QPointer<graphicCycle> cycle)
{
    this->currentHighlightedCycle = cycle;
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
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    int angle = event->angleDelta().y();
    qreal factor;

    // determine which direction the wheel is travelling
    if (angle > 0) {
        factor = 1.1;
        relativeScaleFactor *= 1.1;
    } else {
        factor = 0.9;
        relativeScaleFactor *= 0.9;
    }

    this->scale(factor, factor);
    this->setTransformationAnchor(anchor);
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
 * \brief view::mousePressEvent handle panning on mouse press.
 * \param event mouse event.
 *
 * Checks to see if the view needs panning on a mouse press.
 */
void view::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && panningEnabled) {
        this->panningActive = true;
        this->panningAnchor = event->pos();
        this->setCursor(Qt::ClosedHandCursor);
    }

    // Reimplement standard mouse press event.
    QGraphicsView::mousePressEvent(event);
}


/*!
 * \brief view::mouseMoveEvent
 * \param event
 *
 * Reimplemented event that is triggered when the mouse moves on the view.
 * This allows panning to take place along with detecting when the mouse has stopped.
 */
void view::mouseMoveEvent(QMouseEvent *event)
{
    // Implement standard mouse move event and then add to it
    QGraphicsView::mouseMoveEvent(event);

    // If panning is active, pan.
    if (this->panningActive && !this->panningAnchor.isNull()) {
        this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() - (event->x() - panningAnchor.x()));
        this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - (event->y() - panningAnchor.y()));
        this->panningAnchor = QPoint(event->x(), event->y());
        event->accept();
    }

    // Start a timer to be used to detect when the mouse has stopped moving
    if (!mouseTimeOut->isActive())
        mouseTimeOut->start();

    mouseTimeOut->setInterval(s.value("mouseStopWait").toInt());
}


/*!
 * \brief view::mouseReleaseEvent mouse release event on view.
 * \param event mouse event.
 *
 * Triggered when the mouse is released from the view. This function reimplements the
 * existing function adding panning to it.
 */
void view::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && panningEnabled) {
        this->panningActive = false;
        this->panningAnchor = event->pos();
        QGraphicsView::mouseReleaseEvent(event);
        setCursor(Qt::OpenHandCursor);
    }

    QGraphicsView::mouseReleaseEvent(event);
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

    // if there is no cycle highlighted or a point isn't grabbed find clostest cycle.
    if (currentHighlightedCycle.isNull() ||
            (!currentHighlightedCycle.isNull() && !currentHighlightedCycle->getItemIsGrabbed())) {
        emit highlightClosestCycle(relPoint);
    }
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
