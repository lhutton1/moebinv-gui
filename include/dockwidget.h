#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QObject>
#include <QDockWidget>

class dockWidget : public QDockWidget
{
    Q_OBJECT


public:
    dockWidget(QObject *parent = 0);
    void resizeEvent(QResizeEvent *event);

signals:
    void recenterView();
};

#endif // DOCKWIDGET_H
