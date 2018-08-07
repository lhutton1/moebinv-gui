#ifndef POINT_H
#define POINT_H

#include <QPainter>
#include <figure.h>
#include "drawingmetric.h"
#include "cyclecontextmenu.h"
#include "graphiccycle.h"

/*!
 * \brief The point class
 *
 * Inherits from QGraphicsItem. When created and added to the scene a point is
 * displayed, given the x coordinate, y coordinates.
 */
class point : public graphicCycle
{

public:
    explicit point(MoebInv::figure *f, GiNaC::ex p, QString l);
    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
    void getParameters();

public slots:

signals:

private:

};

#endif // POINT_H
