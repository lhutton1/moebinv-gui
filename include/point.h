#ifndef POINT_H
#define POINT_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsView>
#include <QSettings>

#include <figure.h>

#include "graphiccycle.h"
#include "conf.h"

class point : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    point(double *relativeScaleFactor, struct cycleData data);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QMatrix stableMatrix(const QMatrix &matrix, const QPointF &p) const;
    QRectF boundingRect() const;

private:
    QSettings s;

    double *scaleFactor;
    double x;
    double y;
    QString label;
    QBrush *brush;
    QPen *pen;

    bool BOUNDINGRECT_DEBUG;
};

#endif // POINT_H
