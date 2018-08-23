#include <QDebug>
#include "dockwidget.h"

dockWidget::dockWidget(QObject *parent)
{

}

void dockWidget::resizeEvent(QResizeEvent *event)
{
    emit recenterView();
}
