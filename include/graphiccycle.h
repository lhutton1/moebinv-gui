#ifndef GRAPHICCYCLE_H
#define GRAPHICCYCLE_H

#include <QMenu>
#include <QtMath>
#include <QPainter>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QtMath>

#include "figure.h"

#include "cyclecontextmenu.h"
#include "conf.h"
#include "point.h"
#include "circle.h"
#include "line.h"

/*!
 * \brief The graphicCycle class
 *
 * This class is the base class for all objects drawn on the scene.
 * It contains common fucntions used by a point, circle and line drawing methods.
 *
 * Inherits both QObject and QGraphicsItem.
 *
 */
class graphicCycle : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    graphicCycle(MoebInv::figure *f, GiNaC::ex c);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QString getLabel();
    GiNaC::ex getCycle();
    QMatrix stableMatrix(const QMatrix &matrix, const QPointF &p);
    void addPoint(double x, double y);
    void addCircle(double x, double y, double radius);
    void addLine(double x, double y, double c);
    void buildShape();

public slots:
    void resetRelationalList();
    void addToList(int relType);
    void removeFromList();
    void removeCycle();

signals:
    void removeFromTree(graphicCycle *c);
    void addRelationToList(int relType, GiNaC::ex c);
    void removeRelationFromList(GiNaC::ex c);
    void sceneInvalid();


protected:
    GiNaC::ex cycle;
    MoebInv::figure *fig;
    cycleContextMenu *menu;

    QString label;

    QBrush *brush;
    QPen *pen;
};

#endif // GRAPHICCYCLE_H
