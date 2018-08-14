#ifndef LINE_H
#define LINE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QtMath>

#include "figure.h"

#include "conf.h"

class line : public QGraphicsItem
{
public:
    line(MoebInv::figure *f, double x, double y, double c, QString label, QGraphicsItem *parent, double *relativeScaleFactor);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    QMatrix stableMatrix(const QMatrix &matrix, const QPointF &p);

public slots:


private:
    double x;
    double y;
    double c;
    QString label;
    MoebInv::figure *fig;

    double x1;
    double x2;
    double y1;
    double y2;

    double scaleFactor;

    QBrush *brush;
    QPen *pen;
};

#endif // CIRCLE_H
