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

#include "figure.h"

#include "scene.h"
#include "labels.h"
#include "graphiccycle.h"
#include "conf.h"
#include "view.h"

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
    void addPoint(QPointF location);
    void setDrawingMetric();
    void addToTree(GiNaC::ex cycle);
    void addLineToTree(QString itemName);
    void resetList(GiNaC::lst *list);
    void initTreeModel();
    void initMainMenu();
    void addCycle(GiNaC::ex cycle, QString label);
    void update();
    QString node_compact_string(GiNaC::ex name);
    QString node_label(GiNaC::ex name);
    GiNaC::ex shortestDistance(QPointF point, double dis);
    void resizeEvent(QResizeEvent *event);
    ~MainWindow();

    bool toolAddCycle;

private slots:
    void onMouseScenePress(QPointF point);
    void onMouseSceneHover(QPointF point);
    void addToList(int relType, GiNaC::ex cycle);
    void removeFromList(int relType, GiNaC::ex cycle);
    void on_actionCreate_Cycle_triggered();
    void addInfinityToList(int relType);
    void addRealToList(int relType);
    void addThisToList(int relType);
    void removeInfinityFromList(int relType);
    void removeRealFromList(int relType);
    void removeThisFromList(int relType);
    void on_actionPan_toggled(bool pan);
    void sceneInvalid();
    void findCycleInTree(GiNaC::ex c);
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionNew_triggered();

    void onCustomContextMenu(const QPoint &point);

    void on_actionLabels_toggled(bool labels);

signals:
    void resetRelationalList();

private:
    QSettings s;
    Ui::MainWindow *ui;
    graphicsScene *scene;
    labels *lblGen;

    MoebInv::figure f;

    GiNaC::lst relationList;

    QStandardItemModel *model;

    static const int MENU_SIZE = 3;
    cycleContextMenu *menus[MENU_SIZE];

    QMap<QString, QPointer<graphicCycle>> cyclesMap;

    bool isAddPoint;

    bool REAL_CYCLES;

    QMessageBox *msgBox;

    QToolButton *infinity;
    QToolButton *real;
    QToolButton *thisItem;

    QFileDialog *saveDialog;
};

#endif // MAINWINDOW_H
