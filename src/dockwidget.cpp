#include <QDebug>
#include "dockwidget.h"


/*!
 * \brief dockWidget::dockWidget create a new dock widget with a predetermined size.
 * \param parent
 */
dockWidget::dockWidget(QObject *parent)
{
    this->setSizeRatio(s.value("dockInitialSizeRatio").toDouble());
}


/*!
 * \brief dockWidget::getSizeRatio getter for size ratio.
 * \return double
 */
double dockWidget::getSizeRatio() {
    return this->sizeRatio;
}


/*!
 * \brief dockWidget::setSizeRatio sets the size of the dock widget.
 * \param sizeRatio
 */
void dockWidget::setSizeRatio(double sizeRatio)
{
    this->sizeRatio = sizeRatio;
}


/*!
 * \brief dockWidget::resizeEvent triggered on resize event.
 * \param event
 *
 * makes sure that the dock widget takes up the same ratio of the screen.
 */
void dockWidget::resizeEvent(QResizeEvent *event)
{
    emit calculateDockToWindowPercentage();
    emit recenterView();
}





