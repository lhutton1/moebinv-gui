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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void initFigure();
    void addPoint(QPointF location);
    void setDrawingMetric();
    void addPointToTree(QString itemName);
    void addLineToTree(QString itemName);
    void addCycleToTree(QString itemName);
    ~MainWindow();

    bool toolAddCycle;
    //const double EPSILLION = 0.000000001;

private slots:
    void on_actionCreate_Cycle_toggled(bool toggled);
    void onMouseScenePress(QPointF point);
    //void onMouseSceneHover(QPointF point);
    void removeFromTree(QString label);

private:
    Ui::MainWindow *ui;
    graphicsScene *scene;
    labels *lblGen;

    MoebInv::figure f;
};

#endif // MAINWINDOW_H
