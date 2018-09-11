#ifndef VIEW_H
#define VIEW_H

#include <QSettings>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>
#include <QScrollBar>
#include <qmath.h>

#include "graphiccycle.h"
#include "conf.h"

class view : public QGraphicsView
{
    Q_OBJECT

public:
    explicit view(QObject *parent = 0);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void zoomIn();
    void zoomOut();

    double relativeScaleFactor;
    bool panningEnabled;

signals:
    void highlightClosestCycle(QPointF point);

public slots:
    void recenterView();
    void mouseStopped();

private:
    QSettings s;

    QTimer *mouseTimeOut;

    QPoint dragPos;
    bool panningMouseDown;
    QPoint panningPoint;

};

#endif // VIEW_H
