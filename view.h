#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QApplication>
#include <QScrollBar>
#include <qmath.h>

#include "conf.h"

class view : public QGraphicsView
{
    Q_OBJECT

public:
    explicit view(QObject *parent = 0);
    void wheelEvent(QWheelEvent * event);

    double relativeScaleFactor;

signals:
    void scaleFactorChanged(double relativeScaleFactor);

private:
    Qt::KeyboardModifier modifier;
    QPointF target_scene_pos, target_viewport_pos;
};

#endif // VIEW_H
