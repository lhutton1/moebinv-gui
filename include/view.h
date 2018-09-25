#ifndef VIEW_H
#define VIEW_H

#include <QSettings>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>
#include <QScrollBar>
#include <QMenu>
#include <qmath.h>

#include "graphiccycle.h"
#include "conf.h"

class view : public QGraphicsView
{
    Q_OBJECT

public:
    explicit view(QWidget *parent = nullptr);
    bool getPanningEnabled();
    void setPanningEnabled(const bool &value);
    QPointer<graphicCycle> getCurrentHighlightedCycle();
    void setCurrentHighlightedCycle(const QPointer<graphicCycle> cycle);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void zoomIn();
    void zoomOut();

    double relativeScaleFactor;

signals:
    void highlightClosestCycle(QPointF point);

public slots:
    void recenterView();
    void mouseStopped();
    void setBackgroundColour(QColor colour);

private:
    QSettings s;

    QTimer *mouseTimeOut;
    QMenu *contextMenu;

    bool panningEnabled;
    bool panningActive;
    QPoint panningAnchor;

    QPointer<graphicCycle> currentHighlightedCycle;
};

#endif // VIEW_H
