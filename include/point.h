#ifndef POINT_H
#define POINT_H

#include <QGraphicsItem>
#include <QPainter>
#include <QMenu>
#include <QPointer>
#include <QAction>
#include <QObject>
#include <QGraphicsSceneContextMenuEvent>
#include <figure.h>
#include "drawingmetric.h"

/*!
 * \brief The point class
 *
 * Inherits from QGraphicsItem. When created and added to the scene a point is
 * displayed, given the x coordinate, y coordinates.
 */
class point : public QObject, public QGraphicsItem
{
    Q_OBJECT
    QBrush brush;
    QPen pen;

public:
    explicit point(MoebInv::figure *f, GiNaC::ex p, QString l);
    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *);
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
    void isTangentChecked();
    void isDifferentChecked();
    void resetRelationalList();

signals:
    void removeFromTree(QString label);
    void addOrthogonalToList(int relType, GiNaC::ex c);
    void removeOrthogonalFromList(GiNaC::ex c);

private:
    GiNaC::ex cycle;
    MoebInv::figure *fig;

    double x;
    double y;
    double radius;
    QString label;

    QMenu *menu;

    QPointer<QAction> isOrthogonal = nullptr;
    QPointer<QAction> isfOrthogonal = nullptr;
    QPointer<QAction> isDifferent = nullptr;
    QPointer<QAction> isTangent = nullptr;
    QPointer<QAction> deletePoint = nullptr;
};

#endif // POINT_H
