#ifndef SCENE_H
#define SCENE_H

#include <QSettings>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

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
    bool getPointIsHighlighted();
    void setPointIsHighlighted(const bool &value);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);

signals:
    void newMouseLeftPress(QPointF point);
    void newMouseRightPress(QPointF point);
    void newMouseHover(QPointF point);

private:
    QSettings s;

    bool pointIsHighlighted;
    QMap<GiNaC::ex, QPointer<graphicCycle>> *cycles;
};

#endif // SCENE_H
