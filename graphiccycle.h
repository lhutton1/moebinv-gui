#ifndef GRAPHICCYCLE_H
#define GRAPHICCYCLE_H

#include <QMenu>
#include <QPainter>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>

#include "figure.h"

#include "cyclecontextmenu.h"
#include "drawingmetric.h"


class graphicCycle : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    graphicCycle(MoebInv::figure *f, GiNaC::ex c, QString l);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;
    virtual QRectF boundingRect() const = 0;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void createPointMenu();
    QString getLabel();

public slots:
    void removePoint();
    void isOrthogonalChecked();
    void isfOrthogonalChecked();
    void isTangentChecked();
    void isDifferentChecked();
    void resetRelationalList();

signals:
    void removeFromTree(QString label);
    void addRelationToList(int relType, GiNaC::ex c);
    void removeOrthogonalFromList(GiNaC::ex c);

protected:
    GiNaC::ex cycle;
    MoebInv::figure *fig;

    cycleContextMenu *menu;

    double x;
    double y;
    double radius;
    QString label;

    QBrush brush;
    QPen pen;
};

#endif // GRAPHICCYCLE_H
