#include <QTreeWidgetItem>
#include <QGraphicsTextItem>
#include <QDebug>

#include "scene.h"
#include "point.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace GiNaC;
using namespace MoebInv;

/*!
 * \brief MainWindow::MainWindow
 * \param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // generate graphics view
    scene = new graphicsScene();
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0,0,ui->graphicsView->frameSize().width(),ui->graphicsView->frameSize().height());

    //set up new event
    connect(scene, &graphicsScene::newMousePress, this, &MainWindow::onMouseScenePress);

    //initialize figure
    initFigure();

    //set drawing metric
    metric = drawingMetric::ELLIPTIC;

    //
    lblGen = new labels();
}

/*!
 * \brief MainWindow::~MainWindow MainWindow destructor.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * \brief MainWindow::on_actionCreate_Cycle_toggled Cycle tool toggled
 * \param toggled
 *
 * Called when the cycle tool is toggled on or off. Sets the
 */
void MainWindow::on_actionCreate_Cycle_toggled(bool toggled)
{
    if (toggled) {
        ui->graphicsView->setCursor(Qt::CrossCursor);
        toolAddCycle = true;
    } else {
        ui->graphicsView->setCursor(Qt::ArrowCursor);
        toolAddCycle = false;
    }
}

/*!
 * \brief MainWindow::onMouseScenePress Mouse press on scene.
 * \param point Point at which the mouse was pressed, given in x and y corrdinates.
 */
void MainWindow::onMouseScenePress(QPointF location)
{
    if (toolAddCycle) {
        //addCycle(point);
     } else {
        addPoint(location);
     }

    // future tools here..
    //
    //
}

/*!
 * \brief MainWindow::addCycle Add a cycle to the figure.
 * \param mousePos Coordinates of mouse on the scene.
 *
 * Adds a cycle to the figure then draws it on the scene.
 */
void MainWindow::addPoint(QPointF mousePos) {
    //for point.......
    // gen new label
    QString label = lblGen->genNextLabel();
    // add cycle to the figure
    ex cycle = f.add_point(lst{mousePos.x(),mousePos.y()},qPrintable(label));
    // now draw the point
    point *p = new point(&f, cycle, label);
    scene->addItem(p);
    // now add to tree
    addPointToTree(label);
}

/*!
 * \brief MainWindow::initFigure Initialize figure
 *
 * Create a new figure and apply any additional settings.
 */
void MainWindow::initFigure()
{
    f = figure();

    // Add any additional settings here
    //
    //
}

/*!
 * \brief MainWindow::addPointToTree Add new point to the tree
 * \param itemName point label value.
 */
void MainWindow::addPointToTree(QString itemName)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, itemName);
    ui->treeWidget->addTopLevelItem(item);
}

