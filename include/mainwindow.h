#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPointer>
#include <QTreeWidgetItem>
#include <QGraphicsTextItem>
#include <QMessageBox>

#include <figure.h>

#include "scene.h"
#include "labels.h"
#include "point.h"
#include "circle.h"

namespace Ui {
class MainWindow;
}

/*!
 * \brief The MainWindow class
 *
 * MainWindow, the main application. This encompasses the scene, menu and tree view.
 */
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

private slots:
    void onMouseScenePress(QPointF point);
    void removeFromTree(QString label);
    void addOrthogonalToList(GiNaC::ex cycle);
    void removeOrthogonalFromList(GiNaC::ex cycle);
    void on_actionCreate_Cycle_triggered();

private:
    Ui::MainWindow *ui;
    graphicsScene *scene;
    labels *lblGen;

    MoebInv::figure f;

    GiNaC::lst orthogonalList;

    QTreeWidgetItem *gen1;
    QTreeWidgetItem *gen2;
    QTreeWidgetItem *gen3;

    QMessageBox *msgBox;
};

#endif // MAINWINDOW_H
