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
    void addToTree(graphicCycle *p);
    void addLineToTree(QString itemName);
    void resetList(GiNaC::lst *list);
    void initTreeModel();
    void initMainMenu();
    ~MainWindow();

    bool toolAddCycle;

private slots:
    void onMouseScenePress(QPointF point);
    void onMouseSceneHover(QPointF point);
    void removeFromTree(graphicCycle *c);
    void addOrthogonalToList(int relType, GiNaC::ex cycle);
    void removeOrthogonalFromList(GiNaC::ex cycle);
    void on_actionCreate_Cycle_triggered();
    void addInfinityToList(int relType);
    void addRealToList(int relType);
    void removeInfinityFromList();
    void removeRealFromList();

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

    static const int MENU_SIZE = 3;
    cycleContextMenu *menus[MENU_SIZE];
};

#endif // MAINWINDOW_H
