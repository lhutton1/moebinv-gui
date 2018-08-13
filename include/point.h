#ifndef POINT_H
#define POINT_H

#include <QGraphicsItem>
#include <QPainter>

#include "figure.h"

#include "conf.h"

class point : public QGraphicsItem
{
public:
    point(MoebInv::figure *f, double x, double y, QString label, QGraphicsItem *parent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QMatrix stableMatrix(const QMatrix &matrix, const QPointF &p);
    QRectF boundingRect() const;

private:
    double x;
    double y;
    QString label;
    MoebInv::figure *fig;

    double scaleFactor;

    QBrush *brush;
    QPen *pen;
};

#endif // POINT_H
