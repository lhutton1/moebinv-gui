#ifndef GRAPHICCYCLE_H
#define GRAPHICCYCLE_H

#include <QMenu>
#include <QtMath>
#include <QPainter>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsSceneContextMenuEvent>
#include <QMessageBox>
#include <QtMath>

#include "figure.h"

#include "cyclecontextmenu.h"
#include "view.h"
#include "conf.h"
#include "point.h"
#include "circle.h"
#include "line.h"

/*!
 * \brief The graphicCycle class
 *
 * This class is the base class for all objects drawn on the scene.
 * It contains common fucntions used by a point, circle and line drawing methods.
 *
 * Inherits both QObject and QGraphicsItem.
 *
 */

struct cycleData {
    double x;
    double y;
    double radius;
    double c;
    QString label;
    QGraphicsItem *cycle;
    MoebInv::figure *fig;
    double *relativeScaleFactor;
    class view *view;

    QBrush *brush;
    QPen *pen;
};

class graphicCycle : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    graphicCycle(MoebInv::figure *f, GiNaC::ex c, class view *v, double *relativeScaleFactor, cycleContextMenu *menu);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QString getLabel();
    GiNaC::ex getCycle();
    QMatrix stableMatrix(const QMatrix &matrix, const QPointF &p);
    void addPoint(double x, double y, double *relativeScaleFactor);
    void addCircle(double x, double y, double radius, double *relativeScaleFactor);
    void addLine(double x, double y, double c, double *relativeScaleFactor);
    void buildShape();
    QString node_label(GiNaC::ex name);
    QPointer<cycleContextMenu> getContextMenu();

public slots:
    void resetRelationalList();
    void addToList(int relType);
    void removeFromList(int relType);
    void removeCycle();
    void setHover();
    void unsetHover();

signals:
    void removeFromTree(graphicCycle *c);
    void addRelationToList(int relType, GiNaC::ex c);
    void removeRelationFromList(int relType, GiNaC::ex c);
    void sceneInvalid();
    void scaleFactorChanged();
    void findCycleInTree(GiNaC::ex c);

private:
    GiNaC::ex cycle;
    MoebInv::figure *fig;
    cycleContextMenu *menu;

    double *relativeScaleFactor;

    class view *view;

    QMessageBox *msgBox;

    QString label;

    QBrush *brush;
    QPen *pen;
};

#endif // GRAPHICCYCLE_H
