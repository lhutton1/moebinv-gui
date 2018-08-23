#ifndef LINE_H
#define LINE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QtMath>

#include "figure.h"

#include "graphiccycle.h"
#include "conf.h"
#include "settings.h"

class line : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    line(struct cycleData data);
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
    double c;
    QString label;
    MoebInv::figure *fig;

    double x1;
    double x2;
    double y1;
    double y2;

    double *relativeScaleFactor;

    QBrush *brush;
    QPen *pen;
};

#endif // CIRCLE_H
