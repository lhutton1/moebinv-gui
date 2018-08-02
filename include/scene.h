#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

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

public slots:

signals:
    void newMousePress(QPointF point);
    void newMouseHover(QPointF point);

private:

};

#endif // SCENE_H
