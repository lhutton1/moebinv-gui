#ifndef CIRCLE_H
#define CIRCLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QPainter>
#include <QAction>
#include <QPointer>
#include <QtMath>
#include <figure.h>

#include "drawingmetric.h"
#include "cyclecontextmenu.h"

/*!
 * \brief The circle class
 *
 * Inherits from QGraphicsItem. When created and added to the scene a circle is
 * displayed, given the x coordinate, y coordinate and radius.
 */
class circle : public QObject, public QGraphicsItem
{
    Q_OBJECT
    QBrush brush;
    QPen pen;

public:
    circle(MoebInv::figure *f, GiNaC::ex c, QString l);
    void paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void getParameters();
    void createPointMenu();
    QString getLabel();

public slots:
    void removePoint();
    void isOrthogonalChecked();
    void isfOrthogonalChecked();
    void isDifferentChecked();
    void isTangentChecked();

signals:
    void removeFromTree(QString label);
    void addRelationToList(int relType, GiNaC::ex c);
    void removeOrthagonalFromList(GiNaC::ex c);

private:
    GiNaC::ex cycle;
    MoebInv::figure *fig;

    double x;
    double y;
    double radius;
    QString label;

    cycleContextMenu *menu;
};

#endif // CIRCLE_H
