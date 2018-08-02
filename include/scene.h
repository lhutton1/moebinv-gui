#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class graphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit graphicsScene(QObject *parent = 0);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    //virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);

signals:
    void newMousePress(QPointF point);
    void newMouseHover(QPointF point);

public slots:

private:

};

#endif // SCENE_H
