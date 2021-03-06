#ifndef GRAPHICCYCLE_H
#define GRAPHICCYCLE_H

class point;
class circle;
class line;
class cycleContextMenu;

#include <QSettings>
#include <QtMath>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QMessageBox>
#include <QTimer>
#include <QKeyEvent>

#include <figure.h>

#include "conf.h"
#include "cyclecontextmenu.h"
#include "point.h"
#include "circle.h"
#include "line.h"

/*!
 * \brief The graphicType enum
 *
 * Each of the different child drawing objects.
 * Point - A point on the scene given x and y.
 * Circle - A circle on the scene given x, y and radius.
 * Line - A line on the scene given x, y and c.
 */
enum graphicType {
    POINT,
    CIRCLE,
    LINE
};


/*!
 * \brief The cycleData struct
 *
 * Cycle data that each child object needs.
 */
struct cycleData {
    double x;
    double y;
    double c;
    double radius;
    QBrush *brush;
    QPen *pen;
};


/*!
 * \brief The graphicCycle class
 *
 * This class is the base class for all objects drawn on the scene.
 * It contains common fucntions used by a point, circle and line drawing methods.
 *
 * Inherits both QObject and QGraphicsItem.
 *
 */
class graphicCycle : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    graphicCycle(MoebInv::figure *f, GiNaC::ex c, double *relativeScaleFactor, cycleContextMenu *menu, struct cycleStyleData styleData);
    QString getCycleLabel();
    double* getRelativeScaleFactor();
    cycleContextMenu* getContextMenu();
    bool getItemIsGrabbed();
    void addChild(int childType, const double &x, const double &y, const double &c = 0, const double &radius = 0);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void buildShape();
    QMatrix stableMatrix(const QMatrix &matrix, const QPointF &p);
    bool setCycleAsy(const GiNaC::ex &new_cycle, const struct cycleStyleData &data);
    QString node_label(GiNaC::ex name);
    void setCycleStyle(const struct cycleStyleData &data);

public slots:
    void setHover();
    void unsetHover();
    void setColour(QColor colour);
    void setLineWidth(double weight);
    void setLineStyle(int style);
    void mouseStopped();
    void cancelMovement();

signals:
    void findCycleInTree(GiNaC::ex cycle);
    void sceneInvalid();
    void changesMadeToFigure(const MoebInv::figure &originalFigure, const MoebInv::figure &changedFigure);

private:
    QSettings s;
    QMessageBox *msgBox;

    GiNaC::ex cycle;
    MoebInv::figure *f;
    cycleContextMenu *menu;
    double *relativeScaleFactor;

    bool itemIsHighlighted;
    bool itemIsGrabbed;
    bool itemIsAbleToMove;
    bool itemIsPoint;
    double sceneX;
    double sceneY;

    struct cycleStyleData styleData;
    QBrush *brush;
    QPen *pen;

    QTimer *mouseTimeOut;
};

#endif // GRAPHICCYCLE_H
