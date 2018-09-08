#ifndef CIRCLE_H
#define CIRCLE_H

#include <QSettings>
#include <QGraphicsItem>
#include <QPainter>

#include <figure.h>

#include "graphiccycle.h"
#include "conf.h"

class graphicCycle;

class circle : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    circle(graphicCycle *parent, struct cycleData data);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;

private:
    QSettings s;

    graphicCycle *parent;
    double *scaleFactor;
    double x;
    double y;
    double radius;
    QString label;
    QPen *pen;

    bool BOUNDINGRECT_DEBUG;
};

#endif // CIRCLE_H
