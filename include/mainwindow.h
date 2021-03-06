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
#include <QUndoStack>
#include <QKeyEvent>
#include <QHelpEngine>

#include <figure.h>

#include "scene.h"
#include "labels.h"
#include "conf.h"
#include "view.h"
#include "treemodel.h"
#include "definecycledialog.h"
#include "settingsdialog.h"
#include "figureundocommand.h"
#include "propertiesdialog.h"
#include "helpdialog.h"
#include "graphiccycle.h"

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
    void initialiseDefaultSettings();
    MoebInv::cycle_relation refactorCycleRelation(const GiNaC::ex &relationItem, const GiNaC::ex &newSymbol);
    bool saveCheck();
    void keyPressEvent(QKeyEvent *event);
    void updateFigureProperties();
    void checkDescription();
    GiNaC::ex getMetricType(const int &metric);

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
    void unHighlightCycle();
    void changesMadeToFigure(const MoebInv::figure &originalFigure, const MoebInv::figure &changedFigure);
    void saveDirectoryHasChanged();
    void replaceFigure(const MoebInv::figure &replacementFigure);
    void changeMetric();
    void treeViewClicked(const QModelIndex &index);

    // ui slots
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
    void on_actionFigure_Description_triggered();
    void on_actionQuit_triggered();
    void on_actionDelete_cycle_triggered();
    void on_actionSave_As_triggered();
    void on_actionEllipticPointMetric_triggered();
    void on_actionParabolicPointMetric_triggered();
    void on_actionHyperbolicPointMetric_triggered();
    void on_actionEllipticCycleMetric_triggered();
    void on_actionParabolicCycleMetric_triggered();
    void on_actionHyperbolicCycleMetric_triggered();
    void on_actionPointMetric_hovered();
    void on_actionCycleMetric_hovered();
    void on_actionEvaluationType_hovered();
    void on_actionFloating_triggered();
    void on_actionExact_triggered();

signals:
    void resetRelationalList();
    void escPressed();

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
    QFileDialog *saveDialog;
    settingsDialog *settingDialog;
    propertiesDialog *propDialog;
    helpDialog *applicationHelpDialog;

    QToolButton *defineCycle;
    QToolButton *thisItem;

    GiNaC::ex nextSymbol;
    GiNaC::ex unnamedSymbol;

    QTimer *timer;

    QPointer<graphicCycle> prevHoveredCycle;

    QLabel *statusCoordinates;
    QLabel *statusRelations;

    QMenu *defineCycleMenu;

    QDir saveDirectory;
    bool saved;
    bool defaultDirectoryInUse;

    QUndoStack *undoStack;
};

#endif // MAINWINDOW_H
