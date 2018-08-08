#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPointer>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QGraphicsTextItem>
#include <QMessageBox>
#include <QToolButton>

#include <figure.h>

#include "scene.h"
#include "labels.h"
#include "point.h"
#include "circle.h"
#include "conf.h"

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
    void addPointToTree(point *p);
    void addLineToTree(QString itemName);
    void addCycleToTree(circle *c);
    void resetList(GiNaC::lst *list);
    void initTreeModel();
    void initMainMenu();
    ~MainWindow();

    bool toolAddCycle;

private slots:
    void onMouseScenePress(QPointF point);
    void removeFromTree(QString label);
    void addOrthogonalToList(int relType, GiNaC::ex cycle);
    void removeOrthogonalFromList(GiNaC::ex cycle);
    void on_actionCreate_Cycle_triggered();

signals:
    void resetRelationalList();

private:
    Ui::MainWindow *ui;
    graphicsScene *scene;
    labels *lblGen;

    MoebInv::figure f;

    GiNaC::lst orthogonalList;

    QMessageBox *msgBox;

    QStandardItemModel *model;
};

#endif // MAINWINDOW_H
