#ifndef CIRCLE_H
#define CIRCLE_H

#include "graphiccycle.h"

/*!
 * \brief The circle class
 *
 * When created and added to the scene a circle is
 * displayed, given the x coordinate, y coordinate and radius.
 *
 * Inherits graphicCycle.
 */
class circle : public graphicCycle
{

public:
    circle(MoebInv::figure *f, GiNaC::ex c, QString l, int z);
    void paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;

private:

};

#endif // CIRCLE_H
