#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>

#include <figure.h>

#include "graphiccycle.h"
#include "conf.h"

/*!
 * \brief The graphicsScene class
 *
 * Scene displayed in the main part of the GUI.
 */
class graphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit graphicsScene(QObject *parent = 0);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    int assignMaxZIndex();
    int assignMinZIndex();
    void addToTree(graphicCycle *p);

signals:
    void newMouseLeftPress(QPointF point);
    void newMouseRightPress(QPointF point);
    void newMouseHover(QPointF point);

private:
    QSettings s;

    int maxZValue = 1;
    int minZValue = 0;

    QMap<GiNaC::ex, QPointer<graphicCycle>> *cycles;
};

#endif // SCENE_H
