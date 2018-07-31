#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <figure.h>

#include "scene.h"
#include "labels.h"

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
    void addPoint(QPointF location);
    void removeCycle();
    void drawPoint(GiNaC::ex *cycle);
    void drawLine();
    void drawCycle();
    void setDrawingMetric();
    void addPointToTree(QString itemName);
    void addLineToTree(QString itemName);
    void addCycleToTree(QString itemName);
    ~MainWindow();

    bool toolAddCycle;
    const double EPSILLION = 0.000000001;
    int metric;

private slots:
    void on_actionCreate_Cycle_toggled(bool toggled);
    void onMouseScenePress(QPointF point);

private:
    Ui::MainWindow *ui;
    graphicsScene *scene;
    labels *lblGen;

    MoebInv::figure f;
};

#endif // MAINWINDOW_H
