#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

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
    int assignMaxZIndex();
    int assignMinZIndex();

signals:
    void newMousePress(QPointF point);
    void newMouseHover(QPointF point);

private:
    int maxZValue = 1;
    int minZValue = 0;
};

#endif // SCENE_H
