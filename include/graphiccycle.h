#ifndef GRAPHICCYCLE_H
#define GRAPHICCYCLE_H

#include <QMenu>
#include <QtMath>
#include <QPainter>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>

#include "figure.h"

#include "cyclecontextmenu.h"
#include "conf.h"

/*!
 * \brief The graphicCycle class
 *
 * This class is the base class for all objects drawn on the scene.
 * It contains common fucntions used by a point, circle and line drawing methods.
 *
 * Inherits both QObject and QGraphicsItem.
 *
 * To create a new implementation of graphicCycle:
 * 1. Create a new class
 * 2. Inherit 'graphicCycle as the base class'
 * 3. Invoke the base class constructor
 * 4. Make sure all pure abstract functions have an implementation
 */
class graphicCycle : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    graphicCycle(MoebInv::figure *f, GiNaC::ex c, QString l, int zIndex);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;
    virtual QRectF boundingRect() const = 0;
    virtual void getParameters();
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QString getLabel();
    GiNaC::ex getCycle();

public slots:
    void removeCycle();
    //void isChecked(int relType);
    void resetRelationalList();
    void addToList(int relType);
    void removeFromList();

signals:
    void removeFromTree(QString label);
    void addRelationToList(int relType, GiNaC::ex c);
    void removeRelationFromList(GiNaC::ex c);

protected:
    GiNaC::ex cycle;
    MoebInv::figure *fig;
    cycleContextMenu *menu;

    QString label;

    double x;
    double y;
    double radius;
    int zIndex;

    QBrush *brush;
    QPen *pen;
};

#endif // GRAPHICCYCLE_H
