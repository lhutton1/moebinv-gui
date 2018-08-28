#include <QDebug>
#include "dockwidget.h"

dockWidget::dockWidget(QObject *parent)
{
    this->setSizeRatio(s.value("dockInitialSizeRatio").toDouble());
}

void dockWidget::resizeEvent(QResizeEvent *event)
{
    emit calculateDockToWindowPercentage();
    emit recenterView();
}

void dockWidget::setSizeRatio(double sizeRatio)
{
    this->sizeRatio = sizeRatio;
}

double dockWidget::getSizeRatio() {
    return this->sizeRatio;
}
