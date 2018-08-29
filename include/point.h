#ifndef POINT_H
#define POINT_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsView>
#include <QSettings>

#include "figure.h"

#include "graphiccycle.h"
#include "conf.h"

class point : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    point(struct cycleData data);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QMatrix stableMatrix(const QMatrix &matrix, const QPointF &p) const;
    QRectF boundingRect() const;

private:
    QSettings s;

    double x;
    double y;
    QString label;
    MoebInv::figure *fig;

    double *scaleFactor;

    class view *v;

    bool BOUNDINGRECT_DEBUG;

    QBrush *brush;
    QPen *pen;
};

#endif // POINT_H
