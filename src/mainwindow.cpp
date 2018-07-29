#include <QGraphicsTextItem>
#include <QDebug>

#include "scene.h"
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
}

/*!
 * \brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionMove_Graphics_View_triggered(bool checked)
{
    if (checked)
        ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    else
        ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
}


void MainWindow::on_actionCreate_Cycle_toggled(bool arg1)
{
    if (arg1) {
        ui->graphicsView->setCursor(Qt::CrossCursor);
        toolAddCycle = true;
    } else {
        ui->graphicsView->setCursor(Qt::ArrowCursor);
        toolAddCycle = false;
    }
}

void MainWindow::onMouseScenePress(QPointF point)
{
    if (toolAddCycle)
        addCycle(point);

    // future tools here..
    //
    //
}

/*!
 * \brief graphicsScene::addCycle Add a cycle to the scene.
 * \param mousePos Coordinates of mouse on the scene.
 */
void MainWindow::addCycle(QPointF mousePos) {
    // add cycle to the figure
    f.add_point(lst{mousePos.x(),mousePos.y()},"A");
    // now draw the point
    drawPoint(mousePos.x(), mousePos.y());
}

void MainWindow::removeCycle() {

}

/*!
 * \brief graphicsScene::initFigure Initialize figure
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
 * \brief graphicsScene::drawPoint
 */
void MainWindow::drawPoint(double x, double y)
{
    QPen pen(Qt::black);
    QBrush brush(Qt::black);
    double rad = 2;


    switch(metric) {
        case drawingMetric::ELLIPTIC: {
            scene->addEllipse(x - rad / 2, y - rad / 2, rad, rad, pen, brush);
            QGraphicsTextItem *text = scene->addText("A");
            text->setPos(x + rad, y + rad);
            break;

        } case drawingMetric::PARABOLIC: {
            // reserved for future use
            break;

        } case drawingMetric::HYPERBOLIC: {
            // reserved for future use
            break;
        }
    }
}

/*!
 * \brief graphicsScene::drawLine
 */
void MainWindow::drawLine()
{
    switch(metric) {
        case drawingMetric::ELLIPTIC:
            break;
        case drawingMetric::PARABOLIC:
            // reserved for future use
            break;
        case drawingMetric::HYPERBOLIC:
            // reserved for future use
            break;
    }
}

/*!
 * \brief graphicsScene::drawCycle
 */
void MainWindow::drawCycle()
{
    switch(metric) {
        case drawingMetric::ELLIPTIC:
            break;
        case drawingMetric::PARABOLIC:
            // reserved for future use
            break;
        case drawingMetric::HYPERBOLIC:
            // reserved for future use
            break;
    }
}

