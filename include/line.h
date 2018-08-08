#ifndef LINE_H
#define LINE_H

#include "graphiccycle.h"

/*!
 * \brief The line class
 *
 * When created and added to the scene a line is
 * displayed, given the x coordinate and y coordinates.
 *
 * Inherits graphicCycle.
 */
class line : public graphicCycle
{

public:
    explicit line(MoebInv::figure *f, GiNaC::ex p, QString l, int z);
    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void getParameters() override;

private:
    double x1;
    double x2;
    double y1;
    double y2;
};

#endif // LINE_H
