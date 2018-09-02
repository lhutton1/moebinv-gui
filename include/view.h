#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QApplication>
#include <QScrollBar>
#include <QSettings>
#include <QTimer>
#include <qmath.h>

#include "graphiccycle.h"
#include "conf.h"

class view : public QGraphicsView
{
    Q_OBJECT

public:
    explicit view(QObject *parent = 0);
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void zoomIn();
    void zoomOut();

    double relativeScaleFactor;

signals:
    void highlightClosestCycle(QPointF point);

public slots:
    void recenterView();
    void mouseStopped();

private:
    QSettings s;

    Qt::KeyboardModifier modifier;
    QPointF target_scene_pos, target_viewport_pos;

    QTimer *mouseTimeOut;
};

#endif // VIEW_H
