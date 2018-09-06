#ifndef LINE_H
#define LINE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QtMath>

#include <figure.h>

#include "graphiccycle.h"
#include "conf.h"
#include "settings.h"

class line : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    line(double *relativeScaleFactor, struct cycleData data);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    QMatrix stableMatrix(const QMatrix &matrix, const QPointF &p);
    void findLinePoints();

private:
    QSettings s;
    double *scaleFactor;

    double x;
    double y;
    double c;
    QString label;
    QBrush *brush;
    QPen *pen;

    double x1;
    double x2;
    double y1;
    double y2;
};

#endif // CIRCLE_H
