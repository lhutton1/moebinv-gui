#include <QDebug>
#include "view.h"

view::view(QObject *parent)
{
    this->setRenderHint(QPainter::Antialiasing);
    relativeScaleFactor = 1;
}

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
    qDebug() << relativeScaleFactor;
    emit scaleFactorChanged(relativeScaleFactor);
}
