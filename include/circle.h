#ifndef CIRCLE_H
#define CIRCLE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QSettings>

#include "figure.h"

#include "graphiccycle.h"
#include "conf.h"
#include "settings.h"

class circle : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    circle(struct cycleData data);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    QMatrix stableMatrix(const QMatrix &matrix, const QPointF &p);

signals:
    void isHovered();
    void isUnHovered();

private:
    QSettings s;

    double x;
    double y;
    double radius;
    QString label;
    MoebInv::figure *fig;

    double *relativeScaleFactor;

    bool BOUNDINGRECT_DEBUG;

    QBrush *brush;
    QPen *pen;
};

#endif // CIRCLE_H
