#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <figure.h>

#include "scene.h"

namespace Ui {
class MainWindow;
}

/*!
 * \brief drawingMetric enum
 *
 * 3-types of drawing metric:
 *      elliptic - ...
 *      parabolic - ...
 *      hyperbolic - ...
 */
enum drawingMetric {
    ELLIPTIC,
    PARABOLIC,
    HYPERBOLIC
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void initFigure();
    void addCycle(QPointF mousePos);
    void removeCycle();
    void drawPoint(double x, double y);
    void drawLine();
    void drawCycle();
    void setDrawingMetric();
    ~MainWindow();

    bool toolAddCycle;
    const double EPSILLION = 0.000000001;
    int metric;

private slots:
    void on_actionMove_Graphics_View_triggered(bool checked);
    void on_actionCreate_Cycle_toggled(bool arg1);
    void onMouseScenePress(QPointF point);

private:
    Ui::MainWindow *ui;
    graphicsScene *scene;

    MoebInv::figure f;
};

#endif // MAINWINDOW_H
