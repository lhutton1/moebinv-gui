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
    this->setRenderHint(QPainter::Antialiasing);
    relativeScaleFactor = 1;
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
}
