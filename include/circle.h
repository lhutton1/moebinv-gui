#ifndef CIRCLE_H
#define CIRCLE_H

#include <QGraphicsItem>
#include <QPainter>

#include "figure.h"

#include "conf.h"

class circle : public QGraphicsItem
{
public:
    circle(MoebInv::figure *f, double x, double y, double radius, QString label, QGraphicsItem *parent, double *relativeScaleFactor);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    QMatrix stableMatrix(const QMatrix &matrix, const QPointF &p);

public slots:

private:
    double x;
    double y;
    double radius;
    QString label;
    MoebInv::figure *fig;

    double *relativeScaleFactor;

    QBrush *brush;
    QPen *pen;
};

#endif // CIRCLE_H
