#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QRectF>
#include <figure.h>


class test : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    test();

    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
};

#endif // TEST_H
