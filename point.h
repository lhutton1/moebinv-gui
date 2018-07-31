#ifndef POINT_H
#define POINT_H

#include <QGraphicsItem>
#include <QPainter>
#include <QMenu>
#include <QPointer>
#include <QAction>
#include <QGraphicsSceneContextMenuEvent>
#include <figure.h>
#include "drawingmetric.h"

class point : public QGraphicsItem
{
    QBrush brush;
    QPen pen;

public:
    explicit point(MoebInv::figure *f, GiNaC::ex p, QString l, QGraphicsItem *parent = 0);
    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void getParameters();

private:
    GiNaC::ex cycle;
    MoebInv::figure *fig;

    double x;
    double y;
    double radius;
    QString label;

    QPointer<QAction> isOrthagonal = nullptr;
    QPointer<QAction> isfOrthagonal = nullptr;
    QPointer<QAction> isDifferent = nullptr;
    QPointer<QAction> isTangent = nullptr;
};

#endif // POINT_H
