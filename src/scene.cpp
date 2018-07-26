#include "scene.h"
#include <QtWidgets>

/*!
 * \brief Scene Constructor.
 * \param parent The parent to this current widget.
 *
 * continued description....
 */
scene::scene(QWidget *parent)
    : QFrame(parent)
{
    // create new scene
    sc = new QGraphicsScene;

    //adding objects to the scene
    sc->addRect(QRectF(0, 0, 100, 100));
    sc->addRect(QRectF(-1000, -1000, 100, 100));
    sc->addRect(QRectF(1000, 1000, 100, 100));
    sc->addLine(QLineF(0, -3000, 0, 2000));
}

/*!
 * \brief Scene getter.
 * \return Scene object.
 */
QGraphicsScene *scene::get() const
{
    return static_cast<QGraphicsScene *>(sc);
}

