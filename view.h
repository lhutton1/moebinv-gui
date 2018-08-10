#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QApplication>
#include <QScrollBar>
#include <qmath.h>

#include "conf.h"

class view : public QGraphicsView
{
    Q_OBJECT

public:
    explicit view(QObject *parent = 0);

};

#endif // VIEW_H
