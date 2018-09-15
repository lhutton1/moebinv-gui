#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPointer>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QGraphicsTextItem>
#include <QToolButton>
#include <QMap>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMap>
#include <QSettings>
#include <QTimer>
#include <QLabel>
#include <QRegularExpression>

#include <figure.h>

#include "scene.h"
#include "labels.h"
#include "graphiccycle.h"
#include "conf.h"
#include "view.h"
#include "treemodel.h"
#include "definecycledialog.h"

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
    void setDrawingMetric();
    void addToTree(const GiNaC::ex &cycle, const QColor &colour);
    void addLineToTree(QString itemName);
    void initTreeModel();
    void initMainMenu();
    void addCycle(GiNaC::ex cycle, QString label);
    void update();
    QString node_compact_string(GiNaC::ex name);
    QString node_label(GiNaC::ex name);
    GiNaC::ex shortestDistance(QPointF point, double dis);
    void resizeEvent(QResizeEvent *event);
    struct cycleStyleData getCycleData(const GiNaC::ex& cycle);
    bool setCycleAsy(const GiNaC::ex &new_cycle, const struct cycleStyleData &data);
    void buildToolBar();
    void createCycle(GiNaC::lst inputList = GiNaC::lst());
    ~MainWindow();

    bool toolAddCycle;

private slots:
    void addPoint(QPointF location);
    void onMouseSceneRightPress(const QPointF &point);
    void onMouseSceneHover(const QPointF &point);
    void sceneInvalid();
    void findCycleInTree(const GiNaC::ex &cycle);
    void onCalculateDockRatio();
    void highlightClosestCycle(QPointF point);
    void buildRelationStatus();
    void thisContextMenuUpdate();
    void onCustomContextMenu(const QPoint &point);

    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionNew_triggered();
    void on_actionCreate_Cycle_triggered();
    void on_actionPan_toggled(bool pan);
    void on_actionLabels_toggled(bool labels);
    void on_actionzoomIn_triggered();
    void on_actionzoomOut_triggered();
    void on_actionDebug_bounding_rect_triggered(bool checked);
    void on_actionDefine_by_center_and_radius_squared_triggered();
    void on_actionDefine_by_values_triggered();
    void on_actionDefine_cycle_triggered(int pageIndex = 0);

signals:
    void resetRelationalList();

private:
    QSettings s;
    Ui::MainWindow *ui;
    graphicsScene *scene;
    labels *lblGen;

    MoebInv::figure f;

    GiNaC::lst relationList;

    treeModel *model;

    static const int MENU_SIZE = 3;
    cycleContextMenu *menus[MENU_SIZE];

    QMap<QString, QPointer<graphicCycle>> cyclesMap;

    bool isAddPoint;

    QMessageBox *msgBox;

    QToolButton *defineCycle;
    QToolButton *thisItem;

    GiNaC::ex nextSymbol;

    QFileDialog *saveDialog;

    QTimer *timer;

    QPointer<graphicCycle> prevHoveredCycle;

    QLabel *statusCoordinates;
    QLabel *statusRelations;

    QMenu *defineCycleMenu;
};

#endif // MAINWINDOW_H
