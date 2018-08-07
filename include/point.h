#ifndef POINT_H
#define POINT_H

#include "graphiccycle.h"

/*!
 * \brief The point class
 *
 * When created and added to the scene a point is
 * displayed, given the x coordinate and y coordinates.
 *
 * Inherits graphicCycle.
 */
class point : public graphicCycle
{

public:
    explicit point(MoebInv::figure *f, GiNaC::ex p, QString l);
    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;

private:
    const double DRAWING_RADIUS;
};

#endif // POINT_H
