#ifndef POINT_H
#define POINT_H

#include <QSettings>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsView>

#include <figure.h>

#include "graphiccycle.h"
#include "conf.h"

class graphicCycle;

class point : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    point(graphicCycle *parent, struct cycleData data);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    QSettings s;

    graphicCycle *parent;
    double *scaleFactor;
    double x;
    double y;
    QString label;
    QBrush *brush;
    QPen *pen;

    bool BOUNDINGRECT_DEBUG;
};

#endif // POINT_H
