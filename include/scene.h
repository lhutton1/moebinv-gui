#ifndef SCENE_H
#define SCENE_H

#include <QFrame>
#include <QGraphicsScene>

class scene : public QFrame
{
    Q_OBJECT

public:
    explicit scene(QWidget *parent = 0);

    QGraphicsScene *get() const;
    void addCycle(cycle newCycle);

private:
    QGraphicsScene *sc;
};

#endif // SCENE_H
